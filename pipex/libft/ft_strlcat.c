/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:50:39 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:31 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	len;

	if ((dest == NULL || src == NULL) && dest_size == 0)
		return (0);
	i = 0;
	len = ft_strlen(dest);
	if (dest_size <= len)
		return (dest_size + ft_strlen(src));
	else
	{
		while (src[i] != '\0' && (len + i) < (dest_size - 1))
		{
			dest[len + i] = src[i];
			i++;
		}
	}
	dest[len + i] = '\0';
	return (len + ft_strlen(src));
}

/*Concatenate strings, take the fulll size of the buffer not (not just the
lenght) and guarantee to nul-terminate the result (as long as there is at
least one byte free in 'dest'). Note that a byte for the nul should be included
in 'size'.*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char dest[10];
//     int i = 0;
//     ft_strlcat(dest, "tartine", sizeof(char) * 10);
//     while(dest[i] != '\0')
//     {
//         printf("%c", dest[i]);
//         i++;
//     }
//     printf("\n");
//     char dest2[10];
//     strlcat(dest2, "tartine", sizeof(char) * 10);
//     i = 0;
//     while(dest2[i] != '\0')
//     {
//         printf("%c", dest[i]);
//         i++;
//     }
//     return (0);
// }
