/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:22:14 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 21:28:07 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
TODO : check all errors from process functions
*/

void execute_command(t_cmd cmd, char **env)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd.exec_path, cmd.cmd_and_args, env);
		ft_free_tab(cmd.cmd_and_args);
		free(cmd.exec_path);
		exit(1);
	}
}
