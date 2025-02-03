#include "minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(int pid, int bit)
{
	struct sigaction	sa;

	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	g_ack_received = 0;
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	while (!g_ack_received)
		usleep(10);
}

static void	send_unicode(int pid, wchar_t c)
{
	int	byte_count;
	int	i;

	if (c <= 0x7F)
		byte_count = 1;
	else if (c <= 0x7FF)
		byte_count = 2;
	else if (c <= 0xFFFF)
		byte_count = 3;
	else
		byte_count = 4;
	i = byte_count;
	while (i--)
	{
		send_byte(pid, (c >> (6 * i)) & 0x3F | (i ? 0x80 : 0xFF >> (8 - byte_count)));
	}
}

void	send_message(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			send_bit(pid, (c >> i) & 1);
		}
	}
	i = 8;
	while (i--)
		send_bit(pid, 0);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_message(pid, msg);
	return (0);
}
