#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void send_bit(pid_t pid, int bit) {
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1) exit(1);
    usleep(100); // Prevent signal flooding
}

static void send_char(pid_t pid, char c) {
    for (int i = 7; i >= 0; i--) {
        send_bit(pid, (c >> i) & 1);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID> <message>\n", argv[0]);
        return (1);
    }
    pid_t pid = atoi(argv[1]);
    char *str = argv[2];
    while (*str) send_char(pid, *str++);
    send_char(pid, '\0');
    return (0);
}
