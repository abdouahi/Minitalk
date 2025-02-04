#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char buffer[1024];
    int buffer_index;
    char current_char;
    int bit_count;
    pid_t client_pid;
} client_state;

static client_state state = { .buffer_index = 0, .bit_count = 0, .client_pid = 0 };

static void reset_state() {
    state.buffer_index = 0;
    state.bit_count = 0;
    state.client_pid = 0;
    memset(state.buffer, 0, sizeof(state.buffer));
}

static void signal_handler(int sig, siginfo_t *info, void *context) {
    (void)context;

    if (state.client_pid == 0)
        state.client_pid = info->si_pid;
    else if (state.client_pid != info->si_pid) {
        reset_state();
        state.client_pid = info->si_pid;
    }

    state.current_char |= (sig == SIGUSR1) << state.bit_count;
    state.bit_count++;

    if (state.bit_count == 8) {
        if (state.buffer_index < sizeof(state.buffer) - 1) {
            state.buffer[state.buffer_index] = state.current_char;
            state.buffer_index++;
        }

        if (state.current_char == '\0') {
            write(STDOUT_FILENO, state.buffer, state.buffer_index - 1);
            write(STDOUT_FILENO, "\n", 1);
            reset_state();
        } else if (state.buffer_index >= sizeof(state.buffer) - 1) {
            write(STDOUT_FILENO, state.buffer, sizeof(state.buffer) - 1);
            write(STDOUT_FILENO, "\n", 1);
            reset_state();
        }

        state.current_char = 0;
        state.bit_count = 0;
    }

    kill(info->si_pid, SIGUSR1);
}

int main(void) {
    struct sigaction sa;

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
