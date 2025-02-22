#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack = 0;

static void ack_handler(int sig) {
    (void)sig;
    g_ack = 1;
}

static void send_bit(pid_t pid, int bit) {
    g_ack = 0;
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1)
        exit(EXIT_FAILURE);
    while (!g_ack)
        pause();
}

static void send_char(pid_t pid, char c) {
    for (int i = 0; i < 8; i++) {
        send_bit(pid, (c >> i) & 1);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(2, "Usage: ./client <server_pid> <message>\n", 38);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    while (*message)
        send_char(server_pid, *message++);
    send_char(server_pid, '\0');
    return 0;
}
