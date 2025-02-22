#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack = 0;

static void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

static void send_bit(pid_t pid, char bit)
{
    g_ack = 0;
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1)
        exit(1);
    while (!g_ack)
        pause();
}

static void send_char(pid_t pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        send_bit(pid, (c >> bit) & 1);
        bit--;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <PID> <message>\n", argv[0]);
        return (1);
    }
    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    pid_t pid = atoi(argv[1]);
    char *str = argv[2];
    while (*str)
        send_char(pid, *str++);
    send_char(pid, '\0');
    return (0);
}
