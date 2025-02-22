#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_server {
    char        current_char;
    int         bit_pos;
    char        *message;
    size_t      msg_len;
}               t_server;

static t_server g_data = {0, 0, NULL, 0};

static void reset_state(void) {
    g_data.current_char = 0;
    g_data.bit_pos = 0;
}

static void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)context;
    (void)info;
    int bit = (sig == SIGUSR2);

    g_data.current_char |= (bit << (7 - g_data.bit_pos));
    g_data.bit_pos++;
    if (g_data.bit_pos == 8) {
        if (g_data.current_char == '\0') {
            write(STDOUT_FILENO, g_data.message, g_data.msg_len);
            write(STDOUT_FILENO, "\n", 1);
            free(g_data.message);
            g_data.message = NULL;
            g_data.msg_len = 0;
        } else {
            char *tmp = realloc(g_data.message, g_data.msg_len + 1);
            if (!tmp) exit(EXIT_FAILURE);
            g_data.message = tmp;
            g_data.message[g_data.msg_len++] = g_data.current_char;
        }
        reset_state();
    }
}

int main(void) {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Server PID: %d\n", getpid());
    while (1)
        pause();
    return (0);
}
