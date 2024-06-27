/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:06:09 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/16 15:42:34 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = (char)c;
		i++;
	}
	return (s);
}

/*Fills the first 'n' bytes of the memory area pointed to be 's' with the
constant byte 'c'.*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *buffer[10];
// 	char *buffer2[10];
// 	printf("%s \n", (char *)ft_memset(buffer, 115, sizeof(char) * 5));
// 	printf("%s", (char *) memset(buffer2, 115, sizeof(char) * 5));

// 	return (0);
// }
