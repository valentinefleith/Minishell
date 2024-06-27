/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:34:36 by luvallee          #+#    #+#             */
/*   Updated: 2023/07/12 16:34:39 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(src);
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	else
	{
		ft_memcpy(dup, src, len);
		dup[len] = '\0';
	}
	return (dup);
}

/*Retourne un pointeur sur une nouvelle chaine qui a ete dupliquee de la
chaine 's'. La memoire de la nouvelle chaine est alloue avec malloc.*/

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);
// 	printf("%s", ft_strdup(argv[1]));
// 	return (0);
// }
