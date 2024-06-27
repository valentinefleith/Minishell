/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:51:35 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/21 13:48:10 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	index;
	size_t	len;
	char	*str;

	if (s1 == 0 || set == 0)
		return (NULL);
	index = 0;
	len = ft_strlen(s1) - 1;
	while (s1[index] && ft_is_set(s1[index], set))
		index++;
	if (index > len)
		return (ft_strdup(""));
	while (s1[len] && ft_is_set(s1[len], set))
		len--;
	str = malloc(sizeof(char) * (len - index + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[index], (len - index + 2));
	return (str);
}

/*Alloue et retourne une copie de la chaine 's1'
sans les caracteres specifies dans 'set' au debut et a la fin de la chaine
de caracteres.*/

// str = ft_substr(s1, (unsigned int)index, (len - index + 2));

// #include <stdio.h>
// int	main(void)
// {
// 	char	*s;
// 	s = ft_strtrim("NULL", "\n\t");
// 	// for (int i = 0; s[i] != 0; i++)
// 	printf("%s", s);
// 	free(s);
// 	return (0);
// }
