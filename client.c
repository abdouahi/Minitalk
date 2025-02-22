#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void send_bit(pid_t pid, int bit) {
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1) exit(EXIT_FAILURE);
    usleep(150);
}

static void send_char(pid_t pid, char c) {
    int bit_pos = 7;
    while (bit_pos >= 0) {
        send_bit(pid, (c >> bit_pos) & 1);
        bit_pos--;
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(2, "Usage: ./client <PID> <message>\n", 32);
        return (1);
    }
    pid_t pid = atoi(argv[1]);
    char *str = argv[2];
    while (*str) send_char(pid, *str++);
    send_char(pid, '\0');
    return (0);
}
