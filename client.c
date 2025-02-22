#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void send_bit(pid_t pid, int bit) {
    if (bit) {
        if (kill(pid, SIGUSR2) == -1) exit(EXIT_FAILURE);
    } else {
        if (kill(pid, SIGUSR1) == -1) exit(EXIT_FAILURE);
    }
    usleep(100);
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
        write(STDERR_FILENO, "Usage: ./client <PID> <message>\n", 31);
        return (1);
    }
    pid_t pid = atoi(argv[1]);
    char *str = argv[2];
    while (*str) {
        send_char(pid, *str);
        str++;
    }
    send_char(pid, '\0');
    return (0);
}
