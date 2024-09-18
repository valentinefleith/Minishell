/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:33:05 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/18 13:34:09 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd, int fd)
{
	int	i;

	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		i = 2;
		ft_putstr_fd(cmd[i], fd);
	}
	else if (cmd[1])
	{
		i = 1;
		ft_putstr_fd(cmd[i], fd);
		write(fd, "\n", 1);
	}
	return (0);
}
