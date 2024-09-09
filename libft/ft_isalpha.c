/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:59:30 by val               #+#    #+#             */
/*   Updated: 2024/08/14 16:56:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	for (int i = 0; i < 127; i++)
	{
		if (ft_isalpha(i) == isalpha(i))
			printf("OK\n");
		else
			printf("NOT OK\n char = %c\n ft_isalpha tells %i\n but isalpha tells
				%i\n", i, ft_isalpha(i), isalpha(i));
	}
}
*/
