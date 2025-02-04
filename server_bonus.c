#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CLIENTS 10

typedef struct {
    pid_t pid;
    char buffer[1024];
    int buffer_index;
    char current_char;
    int bit_count;
} client_state;

static client_state clients[MAX_CLIENTS];

static client_state *get_client(pid_t pid) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].pid == pid) return &clients[i];
        if (clients[i].pid == 0) {
            clients[i].pid = pid;
            clients[i].buffer_index = 0;
            clients[i].bit_count = 0;
            clients[i].current_char = 0;
            return &clients[i];
        }
    }
    return NULL;
}

static void signal_handler(int sig, siginfo_t *info, void *context) {
    (void)context;
    client_state *client = get_client(info->si_pid);
    if (!client) return;

    client->current_char |= (sig == SIGUSR1) << client->bit_count;
    client->bit_count++;

    if (client->bit_count == 8) {
        if (client->buffer_index < sizeof(client->buffer) - 1) {
            client->buffer[client->buffer_index++] = client->current_char;
        }

        if (client->current_char == '\0') {
            write(STDOUT_FILENO, client->buffer, client->buffer_index - 1);
            write(STDOUT_FILENO, "\n", 1);
            client->pid = 0;
        } else if (client->buffer_index >= sizeof(client->buffer) - 1) {
            write(STDOUT_FILENO, client->buffer, sizeof(client->buffer) - 1);
            write(STDOUT_FILENO, "\n", 1);
            client->buffer_index = 0;
        }

        client->current_char = 0;
        client->bit_count = 0;
    }

    kill(info->si_pid, SIGUSR1);
}

int main(void) {
    struct sigaction sa;
    memset(clients, 0, sizeof(clients));

    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Server PID: %d\n", getpid());
    while (1) pause();

    return EXIT_SUCCESS;
}
