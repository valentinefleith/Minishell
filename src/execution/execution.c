/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:49:49 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/17 14:04:20 by luvallee         ###   ########.fr       */
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
	shell.read = STDIN_FILENO;
	shell.write = STDOUT_FILENO;
	shell.paths = paths;
	shell.envs = envs;
	if (root && root->type == COMMAND)
	{
		builtin = is_builtin(root->left->item[0]);
		if (builtin != NONE)
			return (ft_free_tab(paths), execute_builtin(builtin, root, root->left->item, envs));
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
		child_process(root->left, shell);
		shell->read = pipe_fd[0];
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
	int	exit_status;
	
	exit_status = 0;
	shell->pid = fork();
	if (shell->pid == 0)
	{
		signal_monitor(true, false);
		shell->read = file_redirection(tree, shell, shell->read, INPUT);
		shell->write = file_redirection(tree, shell, shell->write, OUTPUT);
		if (dup2(shell->read, STDIN_FILENO) == -1)
			perror("dup2: shell->read");
		close_fd(&shell->read);
		if (dup2(shell->write, STDOUT_FILENO) == -1)
			perror("dup2: shell->write");
		close_fd(&shell->write);
		exit_status = cmd_execution(shell, tree);
		exit_child_process(shell, tree, exit_status);
	}
	else if (shell->pid == -1)
		exit_child_process(shell, tree, -12);
	signal_monitor(false, false);
	close_fd(&shell->read);
	close_fd(&shell->write);
}

int	cmd_execution(t_shell *shell, t_btree *tree)
{
	char		*full_cmd_path;
	t_builtin	builtin_type;
	int			exit_status;

	if (tree->type != COMMAND)
		return (-1);
	builtin_type = is_builtin(tree->left->item[0]);
	if (builtin_type != NONE)
		exit_status = execute_builtin(builtin_type, tree, tree->left->item, shell->envs);
	else
	{
		full_cmd_path = get_full_cmd_path(tree->left->item[0], shell->paths);
		exit_status = checking_cmd_access(full_cmd_path);
		if (exit_status == 0)
			execve(full_cmd_path, tree->left->item, shell->envs->env_tab);
		ft_putstr_fd("HELLO\n", 2);
		if (full_cmd_path)
			free(full_cmd_path);
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
		// if (current_pid == -1) // rentre en conflit avec les signaux...
		// 	return (perror("wait"), g_signal);
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

void	exit_child_process(t_shell *shell, t_btree *tree, int exit_status)
{
	if (exit_status == -12)
		perror("fork");
	close_fd(&shell->read);
	close_fd(&shell->write);
	free_process(shell, tree);
	exit(exit_status);
}
