/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:24:16 by abdouahi          #+#    #+#             */
/*   Updated: 2024/11/27 10:01:49 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format_string, ...);
int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr_hex(unsigned long n, int uppercase);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_pointer(void *ptr);
int		ft_putnbr(int n);

#endif