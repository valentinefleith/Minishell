/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:47:08 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/28 18:36:20 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The isalnum() function tests if the character 'c' is an alphanumeric 
 * character.
 * 
 * @param c The character to test.
 * @return 1 if the character is alphanumeric, 0 otherwise.
*/
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int	main()
// {
// 	if (ft_isalnum(54) == 0)
//         printf("error");
//     else
//         printf("je suis alphanum");
// }
