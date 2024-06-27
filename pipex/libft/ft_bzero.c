/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:49:32 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/28 18:30:31 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Erases the data in the 'n' bytes of the memory starting at the location 
 * pointed to by 's', by writing zeros to that area.
 * 
 * @param s The memory area to erase.
 * @param n The number of bytes to erase.
 * 
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/**/

// #include <stdio.h>
// int main()
// {
//     ft_bzero("42", sizeof(char) * 1);
//     return (0);
// }