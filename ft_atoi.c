/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:03:35 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 16:23:13 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	is_a_digit(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i == j)
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int		res;
	int		sign;
	int 	i;

	i = 0;
	sign = 1;
	res = 0;
	is_a_digit(str);
	if ((str[i] == '-' || str[i] == '+' ))
		exit(1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
