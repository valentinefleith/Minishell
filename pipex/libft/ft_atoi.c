/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:49:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/28 18:29:14 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_atoi() function  converts the initial portion of the string pointed
 * to by 'str' to int.
 * 
 * @param str The string to convert.
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_atoi("  ---+--+1234ab567"));
	return (0);
} */
