/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:03:35 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 23:06:23 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int ft_atoi(char *str)
{
    int res;
    int i;

    i = 0;
    res = 0;
    
    if (str[0] == '0' && str[1] != '\0')
        exit(1);
        
    if (!(str[i] >= '0' && str[i] <= '9'))
        exit(1);
        
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    if (str[i] != '\0')
        exit(1);
        
    return (res);
}
