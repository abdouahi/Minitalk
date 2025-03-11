/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:05:26 by abdouahi          #+#    #+#             */
/*   Updated: 2025/03/11 07:30:17 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_pointer(void *ptr)
{
	int	count;

	count = 0;
	count += write(1, "0x", 2);
	count += ft_putnbr_hex((unsigned long)ptr, 0);
	return (count);
}
