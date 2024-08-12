/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:17:49 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 20:12:54 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_nb_of_elem(char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size])
		size++;
	return (size);
}

static char	**ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_strsdup(char **strs)
{
	char	**duplicate;
	size_t	nb_of_elem;
	size_t	i;

	if (!strs)
		return (NULL);
	nb_of_elem = find_nb_of_elem(strs);
	duplicate = malloc((nb_of_elem + 1) * sizeof(char *));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (i < nb_of_elem)
	{
		duplicate[i] = ft_strdup(strs[i]);
		if (!duplicate[i])
			return (ft_free_strs(duplicate));
		i++;
	}
	duplicate[i] = 0;
	return (duplicate);
}

/*# include <stdio.h>
int main() {
	char **strs;
	char **dup;

	strs = ft_split("ls -l -a", ' ');
	dup = ft_strsdup(strs);
	printf("%s, %s, %s\n", dup[0], dup[1], dup[2]);
	ft_free_strs(dup);
	ft_free_strs(strs);

}*/
