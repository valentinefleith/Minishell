/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:16:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 15:46:29 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child_process(t_shell *shell, int exit_status)
{
	if (shell->pid == -1)
		shell->pid = exit_status;
	if (exit_status == -12)
		perror("fork");
	close_fd(&shell->read);
	close_fd(&shell->prev_read);
	close_fd(&shell->write);
	if (shell->pid != -1)
	{
		free_process(shell);
		exit(exit_status);
	}
}

void	free_process(t_shell *shell)
{
	if (shell->paths)
	{
		ft_free_tab(shell->paths);
		shell->paths = NULL;
	}
	if (shell->envs)
		shell->envs = free_envs(shell->envs);
	btree_free(shell->main_root);
	shell->main_root = NULL;
}
