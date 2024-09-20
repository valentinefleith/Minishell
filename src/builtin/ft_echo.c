/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:33:05 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/19 15:55:35 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd, int fd)
{
	int	i;

	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		i = 2;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], fd);
			write(fd, " ", 1);
			i++;
		}
	}
	else
	{
		if (cmd[1])
		{
			i = 1;
			while (cmd[i])
			{
				ft_putstr_fd(cmd[i], fd);
				write(fd, " ", 1);
				i++;
			}
		}
		write(fd, "\n", 1);
	}
	return (0);
}
