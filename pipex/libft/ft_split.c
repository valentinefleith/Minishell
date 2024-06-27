/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:30:55 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/22 12:25:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_substr_len(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
		{
			len++;
			while (s[i] != '\0' && s[i] == c)
				i++;
		}
		i++;
	}
	return (len);
}

static void	ft_malloc_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		free(str);
		i++;
	}
	free(str);
}

static void	ft_init_str(char const *s, char c, char **str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c || s[i] == '\0')
			j = i + 1;
		if ((s[i + 1] == '\0' || s[i + 1] == c) && (s[i] != c))
		{
			str[len] = malloc(sizeof(char) * (i - j + 2));
			if (str[len] == NULL)
				ft_malloc_error(str[len]);
			ft_strlcpy(str[len], (s + j), (i - j + 2));
			len++;
		}
		i++;
	}
	str[len] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_substr_len(s, c) + 1));
	if (str == NULL)
		return (NULL);
	ft_init_str(s, c, str);
	if (str == NULL)
		return (NULL);
	return (str);
}

/*Alloue et retourne un tableau de chaines de caracteres obtenu en separant 's'
a l'aide du caractere 'c', utilise comme delimiteur. Le tableau doit etre
termine par NULL.*/

// #include <stdio.h>

// int	main(void)
// {
// 	char	**str;

// 	str = ft_split("  tripouille  42  ", ' ');
// 	for (int i = 0; str[i] != NULL; i++)
// 	{
// 		printf("%s", str[i]);
// 	}
// 	free(str);
// 	return (0);
// }
