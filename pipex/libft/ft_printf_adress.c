/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_adress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:55:38 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/08 16:50:39 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointer_size(unsigned long long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

int	ft_printf_adress(unsigned long long pointer)
{
	int	count;

	count = 0;
	if (pointer == 0)
		return (count += write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	ft_printf_digit(pointer, 16, 'x');
	return (count + ft_pointer_size(pointer, 16));
}
