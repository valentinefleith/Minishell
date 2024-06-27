/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:56:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/04/24 14:46:03 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	else
	{
		while (s1[j] != '\0')
			str[i++] = s1[j++];
		j = 0;
		while (s2[j] != '\0')
			str[i++] = s2[j++];
		str[i] = '\0';
	}
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s", ft_strjoin("Chapeau ", "pointu"));
// 	// printf("%s", ft_strjoin(NULL, "pointu"));
// 	// printf("%s", ft_strjoin("Chapeau", NULL));
// 	return (0);
// }
