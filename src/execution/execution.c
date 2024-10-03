/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:49:49 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 15:06:08 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_btree *root, t_shell *shell)
{
	int	pipe_fd[2];

	if (!root)
		return (shell->pid);
	if (root->type == COMMAND)
		child_process(root, shell);
	else if (root->type == PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), -1);
		shell->write = pipe_fd[1];
		shell->prev_read = pipe_fd[0];
		child_process(root->left, shell);
		shell->read = pipe_fd[0];
		shell->prev_read = STDIN_FILENO;
		if (root->right && root->right->type != PIPE)
			shell->write = STDOUT_FILENO;
	}
	if (!root->right)
		return (shell->pid);
	else if (root->right->type != PIPE && root->right->type != COMMAND)
		return (shell->pid);
	return (execute_ast(root->right, shell));
}

void	child_process(t_btree *tree, t_shell *shell)
{
	int			exit_status;
	t_builtin	builtin_type;

	exit_status = 0;
	shell->pid = fork();
	if (shell->pid == 0)
	{
		signal_monitor(true, false);
		shell->read = file_redirection(tree, shell, shell->read, INPUT);
		shell->write = file_redirection(tree, shell, shell->write, OUTPUT);
		duplicate_fd(shell);
		if (!tree->left || !tree->left->item)
			exit_child_process(shell, 0);
		builtin_type = is_builtin(tree->left->item[0]);
		if (builtin_type != NONE)
			exit_status = execute_builtin(builtin_type, tree, true, shell);
		else
			exit_status = cmd_execution(shell, tree);
		exit_child_process(shell, exit_status);
	}
	else if (shell->pid == -1)
		exit_child_process(shell, -12);
	signal_monitor(false, false);
	close_fd(&shell->read);
	close_fd(&shell->write);
}

int	cmd_execution(t_shell *shell, t_btree *tree)
{
	char	*full_cmd_path;
	int		exit_status;

	if (tree && tree->type != COMMAND)
		return (-1);
	full_cmd_path = get_full_cmd_path(tree->left->item[0], shell->paths);
	exit_status = checking_cmd_access(tree->left->item[0], full_cmd_path);
	if (exit_status == 0)
		execve(full_cmd_path, tree->left->item, shell->envs->env_tab);
	if (full_cmd_path)
		free(full_cmd_path);
	if (ft_strchr(tree->left->item[0], '/') && exit_status == 0)
	{
		is_directory(tree->left->item[0]);
		exit_status = 126;
	}
	return (exit_status);
}
