/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:39:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 16:02:33 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *find_right_path(char **paths, t_cmd cmd)
{
	return paths[0];
}

t_cmd parse_cmd_executable(char *buffer, char **paths)
{
	t_cmd cmd;

	cmd.cmd_and_args = ft_split(buffer, ' ');
	if (!cmd.cmd_and_args)
		free_and_exit(paths, 2);
	if (!cmd.cmd_and_args[0])
	{
		ft_putendl_fd("bash: cmd not found:", 2);
		ft_free_tab(cmd.cmd_and_args);
		free_and_exit(paths, 2);
	}
	cmd.exec_path = find_right_path(paths, cmd);
	return cmd;
}
