/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:29:03 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 22:59:26 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	send_bit(pid_t pid, int bit)
{
	int	signal;

	if (bit)
		signal = SIGUSR2;
	else
		signal = SIGUSR1;
	if (kill(pid, signal) == -1)
		exit(EXIT_FAILURE);
	usleep(150);
}

static void	send_char(pid_t pid, char c)
{
	int	bit_pos;

	bit_pos = 7;
	while (bit_pos >= 0)
	{
		send_bit(pid, (c >> bit_pos) & 1);
		bit_pos--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;

	if (argc != 3)
	{
		write(2, "Usage: ./client <PID> <message>\n", 32);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
	return (0);
}
