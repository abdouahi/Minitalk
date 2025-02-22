#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_server {
    char        current_char;
    int         bit_pos;
    char        *message;
    size_t      msg_len;
    pid_t       client_pid;
}               t_server;

static t_server g_data;

static void reset_state(void)
{
    g_data.current_char = 0;
    g_data.bit_pos = 0;
}

static void send_ack(void)
{
    if (kill(g_data.client_pid, SIGUSR1) == -1)
        exit(1);
}

static void sig_handler(int sig, siginfo_t *info, void *context)
{
    (void)context;
    g_data.client_pid = info->si_pid;
    g_data.current_char |= (sig == SIGUSR2) << (7 - g_data.bit_pos);
    g_data.bit_pos++;
    if (g_data.bit_pos == 8)
    {
        if (g_data.current_char == '\0')
        {
            write(1, g_data.message, g_data.msg_len);
            write(1, "\n", 1);
            free(g_data.message);
            g_data.message = NULL;
            g_data.msg_len = 0;
        }
        else
        {
            char *tmp = realloc(g_data.message, g_data.msg_len + 1);
            if (!tmp)
                exit(1);
            g_data.message = tmp;
            g_data.message[g_data.msg_len++] = g_data.current_char;
        }
        reset_state();
    }
    send_ack();
}

int main(void)
{
    struct sigaction sa;
    sa.sa_sigaction = sig_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("Server PID: %d\n", getpid());
    while (1)
        pause();
    return (0);
}
