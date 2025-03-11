/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:26:25 by abdouahi          #+#    #+#             */
/*   Updated: 2025/03/11 07:30:51 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_putnbr(int n)
{
	int	count;
	int	num;

	num = n;
	count = 0;
	if (num == -2147483648)
	{
		count = write(1, "-2147483648", 11);
		return (count);
	}
	if (num < 0)
	{
		count += ft_putchar('-');
		num *= -1;
	}
	if (num >= 0 && num <= 9)
	{
		count += ft_putchar(num + '0');
	}
	if (num >= 10)
	{
		count += ft_putnbr(num / 10);
		count += ft_putnbr(num % 10);
	}
	return (count);
}
