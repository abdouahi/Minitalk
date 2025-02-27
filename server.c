/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:29:00 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 15:52:40 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server	g_data = {0, 0, NULL, 0};

static void	reset_state(void)
{
	g_data.current_char = 0;
	g_data.bit_pos = 0;
}

static void	append_char(char c)
{
	char	*new_msg;
	size_t	i;

	new_msg = malloc(g_data.msg_len + 1);
	if (!new_msg)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < g_data.msg_len)
	{
		new_msg[i] = g_data.message[i];
		i++;
	}
	new_msg[g_data.msg_len] = c;
	free(g_data.message);
	g_data.message = new_msg;
	g_data.msg_len++;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_data.current_char |= (sig == SIGUSR2) << (7 - g_data.bit_pos);
	g_data.bit_pos++;
	if (g_data.bit_pos == 8)
	{
		if (g_data.current_char == '\0')
		{
			write(1, g_data.message, g_data.msg_len);
			write(1, "\n", 1);
			free(g_data.message);
			g_data.message = NULL;
			g_data.msg_len = 0;
		}
		else
			append_char(g_data.current_char);
		reset_state();
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	*av = "";
	if(ac > 1)
		exit(1);
	sa = (struct sigaction){0};
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
