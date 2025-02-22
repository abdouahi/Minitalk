#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack_received = 0;

static void ack_handler(int sig) {
    (void)sig;
    g_ack_received = 1;
}

static void send_bit(pid_t pid, int bit) {
    int signal = bit ? SIGUSR2 : SIGUSR1;
    g_ack_received = 0;

    if (kill(pid, signal) == -1) {
        write(STDERR_FILENO, "Kill error\n", 11);
        exit(EXIT_FAILURE);
    }

    while (!g_ack_received) {
        pause();
    }
}

static void send_char(pid_t pid, char c) {
    for (int i = 0; i < 8; i++) {
        int bit = (c >> i) & 1;
        send_bit(pid, bit);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./client PID message\n", 27);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        write(STDERR_FILENO, "Sigaction error\n", 16);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    while (*message) {
        send_char(server_pid, *message);
        message++;
    }
    send_char(server_pid, '\0');
    return 0;
}
