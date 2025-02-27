/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:03:35 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 16:09:00 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	is_a_digit(char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
		j++;
	i = 0;
	if ((str[i] == '-' || str[i] == '+' )
		&& (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
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
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+' ))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
