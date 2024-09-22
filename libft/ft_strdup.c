/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:26:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/22 17:54:34 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	size_of_str_nul;

	if (!s)
		return (NULL);
	size_of_str_nul = ft_strlen(s) + 1;
	duplicate = malloc(size_of_str_nul);
	if (duplicate == NULL)
		return (duplicate);
	ft_strlcpy(duplicate, s, size_of_str_nul);
	return (duplicate);
}
