/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:49:49 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/27 12:36:59 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_pipeline(t_btree *root, t_env *envs, char **paths)
{
	t_shell		shell;
	t_builtin	builtin;

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
		builtin = is_builtin(root->left->item[0]);
		if (builtin != NONE)
			return (execute_builtin(builtin, root, false, &shell));
	}
	execute_ast(root, &shell);
	close_fd(&shell.read);
	close_fd(&shell.write);
	if (access("here_doc", F_OK) != -1)
		unlink("here_doc");
	ft_free_tab(paths);
	return (waiting(&shell, shell.pid));
}

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

void	duplicate_fd(t_shell *shell, bool builtin)
{
	// debug_exec(NULL, shell, 0);
	if (dup2(shell->read, STDIN_FILENO) == -1)
		perror("dup2: shell->read");
	close_fd(&shell->read);
	if (dup2(shell->write, STDOUT_FILENO) == -1)
		perror("dup2: shell->write");
	close_fd(&shell->write);
	(void)builtin;
	// if (builtin == false)
		close_fd(&shell->prev_read);
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
		duplicate_fd(shell, false);
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

	i = 0;
	status = 0;
	while (i < shell->nb_cmd)
	{
		current_pid = wait(&status);
		if (current_pid == last_pid)
		{
			if (WIFSIGNALED(status))
				return (g_signal);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
		i++;
	}
	return (status);
}
