/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:47:25 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/18 21:23:12 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		len = 0;
	if ((unsigned int)len > (unsigned int)ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = (size_t)start;
	j = 0;
	while (j < len && i < (size_t)ft_strlen(s))
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

/*Alloue et retourne une chaine de caracteres issue de la chaine 's'.
Cette nouvelle chaine commence  a l'index 'start' et a pour taille maximale
'len'*/

// #include <stdio.h>
// int	main(void)
// {
// 	char	buffer[] = "g6cljsWupHUBf24 Xy8NxqVvoDMPjT gc76 uo4xhEbvjG2gzy8
//  pVUHWlzq4y hKjqY48UMyrQAcvfN7limbu 5fF0Wo Td3KWaZDxeP 0b3G VClqzrXjAgma
// e Ccx6RWG9HqhZlfbQN py4sYgJxUKdOrD5";
// 	char	*substr;
// 	substr = ft_substr(buffer, 7, 6);
// 	printf("%s", substr);
// 	// expected "upHUBf"
// 	free(substr);
// 	return (0);
// }
