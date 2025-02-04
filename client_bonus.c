#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

volatile sig_atomic_t g_ack_received = 0;

void ack_handler(int sig) {
    (void)sig;
    g_ack_received = 1;
}

void send_bit(pid_t pid, char bit) {
    int retry = 0;
    do {
        g_ack_received = 0;
        if (kill(pid, bit ? SIGUSR1 : SIGUSR2) == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
        while (!g_ack_received && retry < 10) {
            usleep(100);
            retry++;
        }
    } while (!g_ack_received && retry < 10);
}

void send_char(pid_t pid, char c) {
    for (int i = 0; i < 8; i++) {
        send_bit(pid, (c >> i) & 1);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    char *endptr;
    long pid = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || pid <= 0) {
        fprintf(stderr, "Invalid PID\n");
        return EXIT_FAILURE;
    }

    char *message = argv[2];
    while (*message) {
        send_char(pid, *message++);
    }
    send_char(pid, '\0');

    return EXIT_SUCCESS;
}
