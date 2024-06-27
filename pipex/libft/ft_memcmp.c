/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:50:15 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/18 13:13:26 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		n--;
	}
	return (0);
}

/*La fonction compare les 'n' premiers octets (chacun interpretes comme des
unsigned char) des zones de memoire s1 et s2.*/

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     printf("%d \n", ft_memcmp("0", "1", sizeof(char) * 6));
//     printf("%d", memcmp("0", "1", sizeof(char) * 6));
//     return (0);
// }
