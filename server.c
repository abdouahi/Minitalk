#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_server {
    char        current_char;
    int         bit_count;
    pid_t       client_pid;
    char        *message;
    int         lock;
}               t_server;

static t_server g_data = {0};

static void send_ack(pid_t pid) {
    if (kill(pid, SIGUSR1) == -1) {
        exit(EXIT_FAILURE);
    }
}

static void reset_server(void) {
    free(g_data.message);
    g_data.message = NULL;
    g_data.current_char = 0;
    g_data.bit_count = 0;
    g_data.client_pid = 0;
}

static void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)context;
    if (g_data.lock) return;
    g_data.lock = 1;

    if (g_data.client_pid && info->si_pid != g_data.client_pid) {
        send_ack(info->si_pid);
        g_data.lock = 0;
        return;
    }

    g_data.client_pid = info->si_pid;
    if (sig == SIGUSR2) {
        g_data.current_char |= 1 << g_data.bit_count;
    }
    g_data.bit_count++;

    if (g_data.bit_count == 8) {
        if (g_data.current_char == '\0') {
            write(STDOUT_FILENO, g_data.message, strlen(g_data.message));
            write(STDOUT_FILENO, "\n", 1);
            reset_server();
        } else {
            char *new_msg = realloc(g_data.message, 
                (g_data.message ? strlen(g_data.message) : 0) + 2);
            if (!new_msg) {
                free(g_data.message);
                exit(EXIT_FAILURE);
            }
            g_data.message = new_msg;
            size_t len = strlen(g_data.message);
            g_data.message[len] = g_data.current_char;
            g_data.message[len + 1] = '\0';
        }
        g_data.current_char = 0;
        g_data.bit_count = 0;
    }
    send_ack(g_data.client_pid);
    g_data.lock = 0;
}

int main(void) {
    struct sigaction sa;
    char pid_str[20];

    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
        sigaction(SIGUSR2, &sa, NULL) == -1) {
        write(STDERR_FILENO, "Sigaction error\n", 16);
        return 1;
    }

    int len = snprintf(pid_str, 20, "%d\n", getpid());
    write(STDOUT_FILENO, "Server PID: ", 12);
    write(STDOUT_FILENO, pid_str, len);

    while (1) pause();
    return 0;
}
