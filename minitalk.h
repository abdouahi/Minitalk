/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:39:56 by abdouahi          #+#    #+#             */
/*   Updated: 2025/03/15 12:35:15 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format_string, ...);
int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr_hex(unsigned long n, int uppercase);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_pointer(void *ptr);
int		ft_putnbr(int n);

int		ft_atoi(char *str);

#endif