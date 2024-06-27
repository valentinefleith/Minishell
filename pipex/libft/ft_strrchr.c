/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:38:41 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/28 11:13:34 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  The strrchr() function returns a pointer to the last occurrence of the
character c in the string s. return a pointer to the matched character or NULL
if the character is  not  found. The  terminating null byte is considered part
of the string, so that if c is specified as '\0', these functions return a
pointer to the terminator.*/
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	*occurrence;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = 0;
	occurrence = NULL;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			occurrence = &str[i];
		}
		i++;
	}
	return (occurrence);
}

/*Renvoie un pointeur sur la derniere occurrence du caractere 'c' dans la
chaine 's'. L'octet nul final est considere comme faisant partie de la chaine,
de telle sorte que si '\0' est indique pour 'c', on renvoit un pointeur sur
la fin de chaine*/

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%s", ft_strrchr("blablabla", 97));
	printf("%s", strrchr("blablabla", 97));
	return (0);
} */
