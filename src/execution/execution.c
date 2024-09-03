/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:49:49 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/29 12:27:20 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_pipeline(t_btree *tree, t_env *envs, char **paths)
{
	t_shell	shell;
	int 	index;
	
	shell.pid = -1;
	shell.fd_in = -1;
	shell.fd_out = -1;
	shell.nb_cmd = 0;
	shell.nb_cmd = count_cmd(tree, &shell.nb_cmd);
	shell.pipe_fd = creating_pipe(tree);
	if (!shell.pipe_fd)
		return (-1);
	shell.paths = paths;
	shell.envs = envs;
	index = -1;
	execute_pipeline(tree, &shell, index); // protect ?
	close_fd(&shell);
	return (waiting(&shell, shell.pid));
}

void	execute_pipeline(t_btree *tree, t_shell *shell, int index)
{
	if (!tree)
		return ;
	if (tree->type == COMMAND)
		shell->pid = child_process(tree, shell, index + 1);
	else
		shell->pid = child_process(tree->left, shell, index + 1);
	if (!tree->right || tree->right->type != PIPE || tree->right->type != COMMAND)
		return ;
	return (execute_pipeline(tree->right, shell, index));
}

int	child_process(t_btree *tree, t_shell *shell, int index)
{
	t_builtin	builtin_type;
	int			pid;

	if (!tree)
		return (-1);
	builtin_type = is_builtin (tree->left->item[0]);
	if (builtin_type != NONE)
		return (execute_builtin(builtin_type, tree, tree->left->item, shell->envs));
	pid = fork();
	// pid = 0;
	if (pid == 0)
	{
		debug_exec(tree, shell);
		if (fd_redirection(tree, shell, index) == 1)
		{
			close_fd(shell);
			free_process(shell, tree);
			exit(EXIT_FAILURE);
		}
		if (close_fd(shell) == -1)
		{
			free_process(shell, tree);
			exit(EXIT_FAILURE);
		}
		cmd_execution(shell, tree);
	}
	return (pid);
}

int	cmd_execution(t_shell *shell, t_btree *tree)
{
	char		*full_cmd_path;
	int			exit_status;
	
	if (tree->type != COMMAND)
		return (-1);
	full_cmd_path = get_full_cmd_path(tree->left->item[0], shell->paths);
	exit_status = checking_cmd_access(full_cmd_path);
	if (exit_status == 0)
		execve(full_cmd_path, tree->left->item, shell->envs->env_tab);
	close_fd(shell);
	free_process(shell, tree);
	exit(exit_status);
}

int	waiting(t_shell *shell, int last_pid)
{
	int	i;
	int	current_pid;
	int	status;
	
	i = 0;
	status = 0;
	while (i < shell->nb_cmd)
	{
		current_pid = wait(&status);
		if (current_pid == -1)
		{
			
		}
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
		i++;
	}
	return (status);
}
