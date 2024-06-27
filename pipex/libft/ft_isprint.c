/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:48:11 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/16 14:42:05 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int	main()
// {
// 	if (ft_isprint(126) == 0)
//         printf("youre fucking wrong");
//     else
//         printf("je suis printable");  
// }
