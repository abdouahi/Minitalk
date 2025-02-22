#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static volatile sig_atomic_t g_ack = 0;

static void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

static void send_bit(pid_t pid, int bit)
{
    int signal;
    
    g_ack = 0;
    if (bit)
        signal = SIGUSR2;
    else
        signal = SIGUSR1;
    
    if (kill(pid, signal) == -1)
    {
        write(STDERR_FILENO, "Error: Invalid PID\n", 18);
        exit(EXIT_FAILURE);
    }
    while (!g_ack)
        pause();
}

static void send_char(pid_t pid, char c)
{
    int i;
    
    i = 0;
    while (i < 8)
    {
        int bit = (c >> i) & 1;
        send_bit(pid, bit);
        i++;
    }
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    long pid;
    char *endptr;
    
    if (argc != 3)
    {
        write(STDERR_FILENO, "Usage: ./client PID MESSAGE\n", 27);
        return 1;
    }
    
    pid = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || pid <= 0 || pid > PID_MAX)
    {
        write(STDERR_FILENO, "Error: Invalid PID\n", 18);
        return 1;
    }
    
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = ack_handler;
    sigaction(SIGUSR1, &sa, NULL);
    
    while (*argv[2])
        send_char((pid_t)pid, *argv[2]++);
    send_char((pid_t)pid, '\0');
    return 0;
}
