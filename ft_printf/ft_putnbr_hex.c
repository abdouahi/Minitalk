/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:51:51 by abdouahi          #+#    #+#             */
/*   Updated: 2025/03/11 07:31:05 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_putnbr_hex(unsigned long n, int uppercase)
{
	int		count;
	char	*hex;
	char	*hex_upper;

	count = 0;
	hex = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n >= 16)
		count += ft_putnbr_hex(n / 16, uppercase);
	if (uppercase > 0)
		count += ft_putchar(hex_upper[n % 16]);
	else
		count += ft_putchar(hex[n % 16]);
	return (count);
}
