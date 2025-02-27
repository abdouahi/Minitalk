/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdouahi <abdouahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:52:08 by abdouahi          #+#    #+#             */
/*   Updated: 2025/02/27 16:57:34 by abdouahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(char *str)
{
	int i = 0;
	
	while(str[i])
		i++;
	return i;
}

char	*ft_strdup(char *s1)
{
	int		len;
	int		i;
	char	*dup;

	len = 0;
	i = 0;
	len = ft_strlen(s1);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == 0)
		return (0);
	while (i <= len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}