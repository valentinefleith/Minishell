/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:10:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/08 16:50:54 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_string(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		ft_printf_char((int)*str);
		++count;
		++str;
	}
	return (count);
}
