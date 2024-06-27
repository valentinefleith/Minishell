/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:41:41 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/03 14:15:48 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	char	*temp;
	char	*path;

	i = 1;
	if (!env || !child->path || child->executable == 1 || !child->cmd[0])
		ft_execute_executable(pipex, child, 0);
	while (child->path[++i])
	{
		temp = ft_strjoin(child->path[i], "/");
		path = ft_strjoin(temp, child->cmd[0]);
		if (ft_checking_cmd_access(pipex, path) != ERROR)
		{
			free(temp);
			execve(path, child->cmd, env);
			free(path);
			perror(child->cmd[0]);
			break ;
		}
		free(temp);
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
	else if (index == pipex->nb_arg - 1)
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
		if (ft_checking_files_access(pipex, infile) != ERROR)
			ft_opening_file(pipex, infile);
		else
		{
			ft_close_files(pipex, pipex->nb_arg);
			ft_free_everything(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else if (index == pipex->nb_arg - 1)
	{
		ft_opening_file(pipex, outfile);
		if (ft_checking_files_access(pipex, outfile) == ERROR)
		{
			ft_close_files(pipex, pipex->nb_arg);
			ft_free_everything(pipex);
			exit(EXIT_FAILURE);
		}
	}
	ft_duplicate_fd(pipex, index);
	ft_close_files(pipex, pipex->nb_arg);
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
	t_child	*current_child;
	int		index;

	ft_creating_pipe(pipex, count);
	index = 0;
	current_child = pipex->child;
	while (index < count && current_child != NULL)
	{
		current_child->pid = fork();
		if (current_child->pid == ERROR)
			perror("fork");
		else if (current_child->pid == 0)
			ft_child_process(pipex, current_child, index);
		current_child = current_child->next;
		index++;
	}
	ft_close_files(pipex, pipex->nb_arg);
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
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (i < count)
	{
		tmp = wait(&status);
		if (tmp == ERROR)
		{
			ft_putstr_fd("Error: waitpid\n", 2);
			exit(EXIT_FAILURE);
		}
		if (tmp == ft_last_node(pipex->child)->pid)
		{
			pipex->status = 0;
			if (WIFEXITED(status))
				pipex->status = WEXITSTATUS(status);
		}
		i++;
	}
}
