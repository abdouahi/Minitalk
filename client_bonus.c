#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack_received = 0;

static void ack_handler(int sig)
{
    (void)sig;
    g_ack_received = 1;
}

static void send_bit(pid_t pid, int bit)
{
    g_ack_received = 0;
    if (bit)
    {
        if (kill(pid, SIGUSR2) == -1)
            exit(1);
    }
    else
    {
        if (kill(pid, SIGUSR1) == -1)
            exit(1);
    }
    while (!g_ack_received)
        pause();
}

static void send_char(pid_t pid, char c)
{
    int bit_pos;

    bit_pos = 7;
    while (bit_pos >= 0)
    {
        send_bit(pid, (c >> bit_pos) & 1);
        bit_pos--;
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
    {
        send_char(pid, *str);
        str++;
    }
    send_char(pid, '\0');
    return (0);
}
