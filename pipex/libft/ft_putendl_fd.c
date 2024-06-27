/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:50:51 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/15 16:50:58 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/*Ecrit la ligne de caractere 's' sur le descripteur de fichier
donne suivie d'un retour a la ligne*/

// #include <stdio.h>
// int main()
// {
// 	ft_putendl_fd("koala", 1);
// 	return (0);
// }
