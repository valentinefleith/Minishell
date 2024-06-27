/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:59:53 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/04 13:44:22 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * Executes the command by searching for the executable in the given paths.
 * If the executable is found, it is executed using execve().
 * If the executable is not found, ft_execute_executable() is called to handle
 * special case.
 *
 * @param pipex The pipex structure.
 * @param child The child structure containing the child process information.
 * @param env The environment variables.
 */
void	ft_executing(t_pipex *pipex, t_child *child, char **env)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 1;
	if (!env || !child->path || child->executable == 1 || !child->cmd[0])
		ft_execute_executable(pipex, child, 0);
	while (child->path[++i])
	{
		tmp = ft_strjoin(child->path[i], "/");
		path = ft_strjoin(tmp, child->cmd[0]);
		if (ft_checking_cmd_access(pipex, path) != ERROR)
		{
			free(tmp);
			execve(path, child->cmd, env);
			free(path);
			perror(child->cmd[0]);
			pipex->status = ERROR;
			break ;
		}
		free(tmp);
		free(path);
	}
	ft_execute_option(child);
	ft_execute_executable(pipex, child, 0);
}

/**
 * This function duplicates the file descriptors to get the right input/output
 * for the child process at the given index.
 *
 * @param pipex The pipex structure.
 * @param index The index of the current command.
 */
void	ft_duplicate_fd(t_pipex *pipex, int index)
{
	if (index == 0)
	{
		if (dup2(pipex->file_input, STDIN_FILENO) == ERROR
			|| dup2(pipex->fd[index][1], STDOUT_FILENO) == ERROR)
			perror("dup2");
	}
	else if (index == pipex->nb_cmd - 1)
	{
		if (dup2(pipex->fd[index - 1][0], STDIN_FILENO) == ERROR
			|| dup2(pipex->file_output, STDOUT_FILENO) == ERROR)
			perror("dup2");
	}
	else
	{
		if (dup2(pipex->fd[index - 1][0], STDIN_FILENO)
			|| dup2(pipex->fd[index][1], STDOUT_FILENO) == ERROR)
			perror("dup2");
	}
}

/**
 * Executes the child process for the given index in the pipex structure.
 *
 * @param pipex The pipex structure.
 * @param child The child structure containing the child process information.
 * @param index The index of the current command
 */
void	ft_child_process(t_pipex *pipex, t_child *child, int index)
{
	if (index == 0)
	{
		if (ft_checking_file_access(pipex, infile) != ERROR)
			ft_opening_file(pipex, infile);
		else
		{
			ft_closing_files(pipex, pipex->nb_cmd);
			ft_free_everything(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else if (index == pipex->nb_cmd - 1)
	{
		ft_opening_file(pipex, outfile);
		if (ft_checking_file_access(pipex, outfile) == ERROR)
		{
			ft_closing_files(pipex, pipex->nb_cmd);
			ft_free_everything(pipex);
			exit(EXIT_FAILURE);
		}
	}
	ft_duplicate_fd(pipex, index);
	ft_closing_files(pipex, pipex->nb_cmd);
	ft_executing(pipex, child, pipex->env);
}

/**
 * This function is responsible for executing the pipex command.
 * It creates pipes, forks child processes, and processes each command.
 * It also waits for all child processes to finish.
 *
 * @param pipex The pipex structure.
 * @param count The number of commands.
 */
void	ft_pipex(t_pipex *pipex, int count)
{
	int		index;
	t_child	*current_child;

	ft_creating_pipe(pipex, count);
	index = 0;
	current_child = pipex->child;
	while (index < count && current_child != NULL)
	{
		current_child->pid = fork();
		if (current_child->pid == ERROR)
		{
			perror("fork");
			pipex->status = 1;
			return ;
		}
		else if (current_child->pid == 0)
			ft_child_process(pipex, current_child, index);
		index++;
		current_child = current_child->next;
	}
	ft_closing_files(pipex, count);
	ft_waiting(pipex, count, 0);
}

/**
 * Waits for each child processes to finish execution.
 *
 *
 * @param pipex The pipex structure.
 * @param count The number of child processes to wait for.
 */
void	ft_waiting(t_pipex *pipex, int count, int status)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (i != count)
	{
		tmp = wait(&status);
		if (tmp == ERROR)
		{
			ft_putstr_fd("Error: waitpid\n", 2);
			ft_print_error(pipex, NULL, 12);
			exit(EXIT_FAILURE);
		}
		if (tmp == ft_last_node(pipex->child)->pid)
		{
			if (WIFEXITED(status))
				pipex->status = WEXITSTATUS(status);
		}
		i++;
	}
}
