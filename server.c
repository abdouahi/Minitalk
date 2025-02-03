#include "minitalk.h"

static void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		exit(1);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		exit(1);
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	config_signals();
	while (1)
		pause();
	return (0);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_count;
	static unsigned char	c;
	static int				client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		bit_count = 0;
		c = 0;
	}
	c = (c << 1) | (sig == SIGUSR2);
	if (++bit_count == 8)
	{
		if (c == 0)
			kill(client_pid, SIGUSR1);
		ft_printf("%c", c);
		bit_count = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR1);
}
