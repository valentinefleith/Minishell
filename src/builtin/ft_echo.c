/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:33:05 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/26 16:25:53 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_n_option(char **cmd)
{
	int	i;

	if (!cmd[1])
		return (false);
	if (ft_strncmp(cmd[1], "-n", 2))
		return (false);
	i = 1;
	while (cmd[1][i])
	{
		if (cmd[1][i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	find_index_to_start(char **cmd)
{
	int	starting_index;

	starting_index = 2;
	while (cmd[starting_index])
	{
		if (!find_n_option(cmd + starting_index - 1))
			return (starting_index);
		starting_index++;
	}
	return (starting_index);
}

static int	option_echo(char **cmd, int fd)
{
	int	index;

	index = find_index_to_start(cmd);
	while (cmd[index])
	{
		ft_putstr_fd(cmd[index], fd);
		if (cmd[index + 1])
			write(fd, " ", 1);
		index++;
	}
	return (0);
}

static int	regular_echo(char **cmd, int fd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	write(fd, "\n", 1);
	return (0);
}

int	ft_echo(char **cmd, int fd)
{
	bool	has_n_option;

	has_n_option = find_n_option(cmd);
	if (!has_n_option)
		return (regular_echo(cmd, fd));
	return (option_echo(cmd, fd));
}
