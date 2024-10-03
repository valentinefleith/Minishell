/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:34:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 15:59:53 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_pipeline(t_btree *root, t_env *envs, char **paths)
{
	t_shell		shell;
	t_builtin	builtin;

	builtin = NONE;
	shell.pid = -1;
	shell.nb_cmd = 0;
	count_cmd(root, &shell.nb_cmd);
	shell.prev_read = STDIN_FILENO;
	shell.read = STDIN_FILENO;
	shell.write = STDOUT_FILENO;
	shell.paths = paths;
	shell.envs = envs;
	shell.main_root = root;
	if (root && root->type == COMMAND)
	{
		if (root->left && root->left->item)
			builtin = is_builtin(root->left->item[0]);
		if (builtin != NONE)
			return (execute_builtin(builtin, root, false, &shell));
	}
	execute_ast(root, &shell);
	close_fd(&shell.read);
	close_fd(&shell.write);
	ft_free_tab(paths);
	return (waiting(&shell, shell.pid));
}

void	duplicate_fd(t_shell *shell)
{
	if (dup2(shell->read, STDIN_FILENO) == -1)
		perror("dup2: shell->read");
	close_fd(&shell->read);
	if (dup2(shell->write, STDOUT_FILENO) == -1)
		perror("dup2: shell->write");
	close_fd(&shell->write);
	close_fd(&shell->prev_read);
}

int	close_fd(int *fd)
{
	if (*fd >= 0 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO)
	{
		if (close(*fd) == -1)
			return (perror("Closing fd failed"), 1);
		*fd = -1;
	}
	return (0);
}

int	waiting(t_shell *shell, int last_pid)
{
	int	i;
	int	current_pid;
	int	status;
	int	return_status;

	i = 0;
	status = 0;
	return_status = 0;
	while (i < shell->nb_cmd)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid == last_pid)
		{
			if (WIFSIGNALED(status))
				return_status = g_signal;
			if (WIFEXITED(status))
				return_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (return_status);
}
