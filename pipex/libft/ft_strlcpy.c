/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:49:00 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/18 14:02:45 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, unsigned int dest_size)
{
	size_t	i;

	i = 0;
	if (dest_size == 0)
		return (ft_strlen(src));
	else
	{
		while (src[i] != '\0' && i < dest_size - 1)
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

// si la boucle a ete interrompue parce que 'dest_size' a ete atteint on 
// continue de compter la longueur de 'src' jusqu'au caractere nul.

/*Copies at most 'dest' size -1 characters from 'src' to 'dest', truncatting
'src' if necessary. The result is always null-terminated. The fuction returns
strlen(src). And the buffer overflow can be checked.*/

/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	unsigned int size = 7;

	char	destination[7] = "bjr";
	char	source[7] = "ouinon";

	char	destination1[7] = "carotte";
	printf("%i\n", ft_strlcpy(destination, source, size));
	printf("%s\n", destination);

	printf("%li", strlcpy(destination1, source, size));
	return (0);
}
*/
