/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:08:11 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/16 19:16:41 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

/*Copie 'n' octets depuis la zone de memoire src vers la zone memoire dest.
Les deux zones ne doivent pas se chevaucher. Si c'est le cas il faut plutot
utiliser 'memmov'.e*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char dest[8];
// 	char dest2[8];
// 	ft_memcpy(dest, "brioche", sizeof(char) * 7);
// 	memcpy(dest2, "brioche", sizeof(char) * 7);
// 	for(int i = 0; i < 8; i++)
// 	{
// 		printf("%c", dest[i]);
// 	}
// 	printf("\n");
// 	for(int i = 0; i < 8; i++)
// 	{
// 		printf("%c", dest2[i]);
// 	}
// 	return (0);
// }
