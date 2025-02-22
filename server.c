#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_server {
    pid_t           client_pid;
    unsigned char   current_char;
    char            *message;
    int             bit_count;
}               t_server;

static t_server g_server = {0, 0, NULL, 0};

static void send_ack(pid_t pid) {
    if (kill(pid, SIGUSR1) == -1) {
        exit(EXIT_FAILURE);
    }
}

static void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)context;
    g_server.client_pid = info->si_pid;
    if (sig == SIGUSR1)
        g_server.current_char |= 0 << g_server.bit_count;
    else
        g_server.current_char |= 1 << g_server.bit_count;
    g_server.bit_count++;
    if (g_server.bit_count == 8) {
        if (g_server.current_char == '\0') {
            write(1, g_server.message, strlen(g_server.message));
            write(1, "\n", 1);
            free(g_server.message);
            g_server.message = NULL;
        } else {
            char *temp = g_server.message;
            g_server.message = malloc((g_server.message ? strlen(g_server.message) : 0) + 2);
            if (!g_server.message) {
                free(temp);
                exit(EXIT_FAILURE);
            }
            if (temp) {
                strcpy(g_server.message, temp);
                free(temp);
            } else {
                g_server.message[0] = '\0';
            }
            strncat(g_server.message, &g_server.current_char, 1);
        }
        g_server.current_char = 0;
        g_server.bit_count = 0;
    }
    send_ack(g_server.client_pid);
}

int main(void) {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    write(1, "Server PID: ", 12);
    char pid_str[20];
    int len = sprintf(pid_str, "%d\n", getpid());
    write(1, pid_str, len);

    while (1)
        pause();
    return 0;
}
