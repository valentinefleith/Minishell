/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:13:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/03 17:01:40 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s + i);
	return (NULL);
}

/*Renvoie un pointeur sur la premiere occurence du caractere 'c' 
dans la chaine 's'. Si '\0' est indique pour 'c' renvoie un pointeur sur la 
fin de la chaine*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	printf("%s", ft_strchr("fromage \n", 'e'));
// 	printf("%s", strchr("fromage", 'e'));
// 	return (0);
// }