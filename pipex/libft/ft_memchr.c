/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:59:39 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/18 13:07:08 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

/*Examine les 'n' premiers octets de la memoire pointee par 's' a 
la recherche de la premiere occurence 'c'. A la fois 's' et les octets
de la memoire pointee par 's' sont interpretes comme des unsigned char*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char data[];
// 	data = ft_memchr("bonjour", 'j', 6);
// 	printf("%c",data[0]);
// 	return (0);
// }