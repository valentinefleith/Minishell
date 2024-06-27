/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:30:31 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/19 18:34:27 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	if (nb > 0)
		ft_putchar_fd((nb % 10 + '0'), fd);
	else
		ft_putchar_fd(n + '0', fd);
}

/* Ecrit l'entier 'n' sur le descripteur de fichier donne*/

// int main()
// {
// 	ft_putnbr_fd(-2147483648, 1);
// 	return (0);
// }