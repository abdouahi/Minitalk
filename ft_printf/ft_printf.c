/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:23:45 by abdouahi          #+#    #+#             */
/*   Updated: 2024/12/03 09:58:01 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (format == 'p')
		return (ft_pointer(va_arg(args, void *)));
	if (format == 'i' || format == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (format == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (format == 'x' || format == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), format == 'X'));
	return (ft_putchar(format));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += handle_format(format[++i], args);
		else if (format[i] == '%' && format[i + 1] == '\0')
			return (count);
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
