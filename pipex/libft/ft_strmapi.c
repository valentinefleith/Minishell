/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:17:32 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/19 18:45:46 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*str;

	if (s == NULL || f == NULL)
		return (0);
	i = 0;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (0);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* Applique la fonction 'f' a chaque caractere de la chaine de caractere
passee en argument pour creer une nouvelle chaine de caracteres (avec malloc)
resultant des applications successives de 'f'*/

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_strmapi("string", ));
// 	return (0);
// }