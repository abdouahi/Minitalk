/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:11:47 by abdouahi          #+#    #+#             */
/*   Updated: 2025/03/11 07:30:59 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}
