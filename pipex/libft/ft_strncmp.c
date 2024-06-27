/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:33:00 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/04 11:39:34 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two strings up to a specified number of characters.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (n <= 0)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] || (i >= (n - 1)))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//&& s1[i] == s2[i]

/* Compare les 'n' premiers octets des deux chaine 's1' et 's2'.*/

// #include <stdio.h>

// #include <string.h>

// int main()
// {
// 	char *lim = "lim\n";
// 	printf("%d\n", ft_strncmp(&lim[3], "\n", 1));
// 	// printf("%d", strncmp("yolim\nyi lim\nlime\nlim", "lim",
			// ft_strlen("yolim\nyi lim\nlime\nlim")));
// 	return (0);
// }