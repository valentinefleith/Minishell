/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:23:17 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/19 18:50:14 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	len;
	char	*str;
	long	nb;

	len = ft_nblen(n);
	nb = n;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[len] = '\0';
	while (len-- && nb != 0)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/*Alloue et retourne une chaine de caracteres representant l'entier 'n'
 recu en argument. Les nombres negatifs doivent etre geres*/

// #include <stdio.h>
// int main()
// {
// 	char *n = ft_itoa(9);
//     printf("%s", n);
// 	free(n);
//     return (0);
// }
