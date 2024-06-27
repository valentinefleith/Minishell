/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:08:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/28 18:34:20 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The calloc() function allocates memory for an array of 'count' elements of
 * 'size' bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero. 
 * 
 * @param count The number of elements to allocate.
 * @param size The size of each element.
 * @return If 'count' or 'size' is 0, returns either NULL, or a unique pointer
 * value  that can later be successfully passed to free().
 * 
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	if (((long long) size < 0 && (long long)count != 0)
		|| ((long long) size != 0 && (long long)count < 0))
		return (NULL);
	pointer = malloc(count * size);
	if (pointer == NULL)
		return (0);
	ft_bzero(pointer, (count * size));
	return (pointer);
}

/*Alloue la memoire necessaire pour un tableau de 'count' elements de 'size' 
octets et renvoie un pointeur vers la memoire allouee. Cette zone est remplie
avec des zeros. Si 'count' ou 'size' est nulle, calloc renvoie NULL ou un 
unique pointeur qui pourra etre passe ulterieurement a free avec succes*/

// #include <stdio.h>
// int	main()
// {
// 	char	*str;
// 	str = ft_calloc(30, 1);
// 	if (str != NULL)
// 		printf("ok");
// 	else
// 		printf("error");
// 	free(str);
// 	return (0);
// }