#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct s_server {
    int     current_bit;
    char    current_char;
    pid_t   client_pid;
    char    *message;
} t_server;

static t_server g_data = {0};

static void reset_state(void) {
    free(g_data.message);
    g_data.message = NULL;
    g_data.current_bit = 0;
    g_data.current_char = 0;
    g_data.client_pid = 0;
}

static void build_message(void) {
    if (g_data.current_char == '\0') {
        ft_printf("%s\n", g_data.message);
        reset_state();
        kill(g_data.client_pid, SIGUSR1);
        return;
    }
    
    size_t len = g_data.message ? ft_strlen(g_data.message) : 0;
    char *tmp = ft_realloc(g_data.message, len + 2);
    if (!tmp) {
        reset_state();
        return;
    }
    g_data.message = tmp;
    g_data.message[len] = g_data.current_char;
    g_data.message[len + 1] = '\0';
}

static void sig_handler(int sig, siginfo_t *info, void *context) {
    (void)context;
    if (g_data.client_pid && info->si_pid != g_data.client_pid) {
        reset_state();
        kill(info->si_pid, SIGUSR2);
        return;
    }
    
    if (!g_data.client_pid) 
        g_data.client_pid = info->si_pid;
    
    g_data.current_char = (g_data.current_char << 1) | (sig == SIGUSR2);
    
    if (++g_data.current_bit == 8) {
        build_message();
        g_data.current_bit = 0;
        g_data.current_char = 0;
    }
    kill(g_data.client_pid, SIGUSR1);
}

int main(void) {
    ft_printf("Server PID: \033[96m%d\033[0m\n", getpid());
    
    struct sigaction sa = {
        .sa_sigaction = sig_handler,
        .sa_flags = SA_SIGINFO
    };
    
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();
    return 0;
}
