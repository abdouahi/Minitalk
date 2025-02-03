#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

volatile sig_atomic_t g_ack = 0;

static void ack_handler(int sig) {
    (void)sig;
    g_ack = 1;
}

static void send_signal(pid_t pid, int bit) {
    int sig = bit ? SIGUSR2 : SIGUSR1;
    if (kill(pid, sig) == -1) {
        ft_putstr_fd("Error: Invalid PID\n", 2);
        exit(EXIT_FAILURE);
    }
}

static void transmit_char(char c, pid_t pid) {
    for (int i = 7; i >= 0; i--) {
        g_ack = 0;
        send_signal(pid, (c >> i) & 1);
        while (!g_ack) {
            usleep(50);
            if (!g_ack) {
                ft_putstr_fd("Error: No server response\n", 2);
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 3 || !ft_strisdigit(argv[1])) {
        ft_printf("Usage: %s <PID> <message>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sigaction sa = {
        .sa_handler = ack_handler,
        .sa_flags = 0
    };
    
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    
    pid_t pid = ft_atoi(argv[1]);
    char *msg = argv[2];

    while (*msg)
        transmit_char(*msg++, pid);
    
    transmit_char('\0', pid);
    return EXIT_SUCCESS;
}
