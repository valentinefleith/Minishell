/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:50:25 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/22 12:12:15 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	if (dest == 0 && src == 0)
		return (NULL);
	if (src > dest)
	{
		dest_temp = ft_memcpy(dest, src, n);
		return (dest_temp);
	}
	else
	{
		dest_temp = (unsigned char *)dest;
		src_temp = (unsigned char *)src;
		while (n > 0)
		{
			dest_temp[n - 1] = src_temp[n - 1];
			n--;
		}
		return (dest_temp);
	}
}

/*Copie 'n' octets depuis la zone memoire src vers la zone memoire 'dest'. 
Les deux zones peuvent se chevaucher : la copie s'effectue comme si 'src'
etait premierement copiee dans un tableau ne chevauchant pas 'src' ou 'dest'
puis il est copie vers 'dest'.*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char buffer[5];
//     char buffer2[5];
//     ft_memmove(buffer, "noix", sizeof(char) * 5);
//     memmove(buffer2, "noix", sizeof(char) * 5);
//     for(int i = 0; i < 5; i++)
//         printf("%c", buffer[i]);
//     printf("\n");
//     for(int i = 0; i < 5; i++)
//         printf("%c", buffer[i]);
//     return (0);
// }
