/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:28 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/16 14:46:30 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if ((char)c >= 97 && (char)c <= 122)
		return (c - 32);
	else
		return (c);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	printf("%d \n", ft_toupper(97));
// 	printf("%d", toupper(97));
// 	return (0);
// }
