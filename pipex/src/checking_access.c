/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:52 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/31 15:26:35 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * Check if the specified file exists and if the user has the necessary
 * permissions to read or write to it.
 *
 * @param pipex The pipex structure.
 * @param file The file to check (infile or outfile).
 * @return 0 if the file exists and the user has the necessary permissions,
 *         or an error code if not.
 */
int	ft_checking_files_access(t_pipex *pipex, t_file file)
{
	if (file == infile)
	{
		if (access(pipex->infile, F_OK) != ERROR)
		{
			if (access(pipex->infile, R_OK) == ERROR)
				return (perror(pipex->infile), ERROR);
		}
		else
			return (perror(pipex->infile), ERROR);
	}
	else if (file == outfile)
	{
		if (access(pipex->outfile, W_OK) == ERROR)
			return (perror(pipex->outfile), ERROR);
	}
	return (0);
}

/**
 * This function checks if the specified command exists and if the user has the
 * necessary permissions to execute it.
 *
 * @param pipex The pipex structure.
 * @param path The path to the command.
 * @return 0 if the command exists and the user has the necessary permissions,
 *         or an error code if not
 */
int	ft_checking_cmd_access(t_pipex *pipex, char *path)
{
	if (!path)
	{
		pipex->status = 127;
		return (ERROR);
	}
	if (access(path, F_OK) == ERROR)
	{
		pipex->status = 127;
		return (ERROR);
	}
	if (access(path, X_OK) == ERROR)
	{
		pipex->status = 126;
		return (ERROR);
	}
	pipex->status = 0;
	return (0);
}

/**
 * Opens the input and output files based on the given file type.
 *
 * @param pipex The pipex struct.
 * @param file The type of file to open (infile or outfile).
 */
void	ft_opening_file(t_pipex *pipex, t_file file)
{
	if (file == infile)
	{
		pipex->file_input = open(pipex->infile, O_RDONLY);
		if (pipex->file_input == ERROR)
		{
			perror(pipex->infile);
			pipex->status = 1;
		}
	}
	else if (file == outfile)
	{
		pipex->file_output = open(pipex->outfile, O_RDWR | O_CREAT | O_TRUNC,
				0644);
		if (pipex->file_output == ERROR)
		{
			perror(pipex->outfile);
			ft_close_files(pipex, pipex->nb_arg);
			ft_free_everything(pipex);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_execute_option(t_child *child)
{
	if (child->cmd_path != NULL)
	{
		if (access(child->cmd_path, F_OK) != ERROR)
		{
			execve(child->cmd_path, child->cmd, NULL);
			perror(child->cmd_path);
		}
	}
}

/* If no path have been found, try to execute the cmd as an executable. If it
doesn't work, prints error, closes, frees everything and exit. */
void	ft_execute_executable(t_pipex *pipex, t_child *child, int signal)
{
	ft_execute_option(child);
	if (child->cmd[0] != NULL)
	{
		if (access(child->cmd[0], F_OK) == ERROR)
			signal = 127;
		else if (access(child->cmd[0], X_OK) == ERROR)
			signal = 126;
		else
			signal = 0;
	}
	else
		signal = 127;
	if (signal == 0 && child->cmd[0] != NULL)
	{
		execve(child->cmd[0], child->cmd, pipex->env);
		perror(child->cmd[0]);
	}
	ft_print_error(pipex, child, signal);
	ft_close_files(pipex, pipex->nb_arg);
	ft_free_everything(pipex);
	exit(signal);
}
