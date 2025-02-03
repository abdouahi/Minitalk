#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

volatile sig_atomic_t g_bit_ack = 0;
volatile sig_atomic_t g_msg_ack = 0;

static void handle_bit_ack(int sig) { (void)sig; g_bit_ack = 1; }
static void handle_msg_ack(int sig) { (void)sig; g_msg_ack = 1; }

static void send_unicode(pid_t pid, const char *msg) {
    for (; *msg; msg++) {
        for (int i = 7; i >= 0; i--) {
            g_bit_ack = 0;
            kill(pid, ((*msg >> i) & 1) ? SIGUSR2 : SIGUSR1);
            while (!g_bit_ack) {
                usleep(50);
                if (!g_bit_ack && kill(pid, 0) == -1) {
                    ft_putstr_fd("Connection lost\n", 2);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 3 || !ft_strisdigit(argv[1])) {
        ft_printf("Usage: %s <PID> \"Message\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sigaction sa_bit = {.sa_handler = handle_bit_ack};
    struct sigaction sa_msg = {.sa_handler = handle_msg_ack};
    sigaction(SIGUSR1, &sa_bit, NULL);
    sigaction(SIGUSR2, &sa_msg, NULL);

    pid_t pid = ft_atoi(argv[1]);
    const char *msg = argv[2];

    send_unicode(pid, msg);
    send_unicode(pid, "\0");

    int timeout = 10000;
    while (!g_msg_ack && timeout--) usleep(100);
    if (!g_msg_ack) {
        ft_putstr_fd("Error: Server timeout\n", 2);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
