/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:10:23 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/16 14:46:47 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((char)c >= 65 && (char)c <= 90)
		return (c + 32);
	else
		return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// 	printf("%d \n", ft_tolower(82));
// 	printf("%d", tolower(82));
// 	return (0);
// }
