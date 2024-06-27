/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:34:43 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/19 18:45:37 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	if (s == NULL)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

/* Applique la fonction 'f' a chaque caractere de la chaine de caracteres
transmise comme argument, et en passant son index comme premier argument.
Chaque caractere est transmis par adresse a 'f' afin d'etre modifie si
necessaire */

// void
// iter(unsigned int i, char * s) {
// 	*s += i;
// }
// #include <stdio.h>
// int main()
// {
// 	char str[] = "0";
// 	ft_striteri(str, iter);
// 	return (0);
// }