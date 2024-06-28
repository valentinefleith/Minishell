/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:13:08 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/28 09:16:54 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Calls every functions necessary to clean up all the program */
void	ft_free_everything(t_pipex *pipex)
{
	ft_deleting_list(&pipex->child);
	ft_deleting_fd(pipex->fd, pipex->nb_cmd);
}

/**
 * Counts the number of arguments and commands in the pipex structure.
 *
 * @param pipex The pipex structure.
 * @param argc The number of command line arguments.
 */
void	ft_count_arg(t_pipex *pipex, int argc)
{
	pipex->nb_arg = argc - 1;
	if (pipex->here_doc.here == TRUE)
		pipex->nb_cmd = pipex->nb_arg - 3;
	else
		pipex->nb_cmd = pipex->nb_arg - 2;
}

/**
 * Creates the necessary number of pipes based on the count.
 *
 * @param pipex The pipex struct.
 * @param count The number of pipes to create.
 */
void	ft_creating_pipe(t_pipex *pipex, int count)
{
	int	i;

	i = 0;
	while (count != 0)
	{
		if (pipe(pipex->fd[i]) == ERROR)
		{
			perror("pipe");
			pipex->status = 0;
			return ;
		}
		count--;
		i++;
	}
}

/**
 * Deletes the path of the command in input and returns it, BUT saves the path
 * with the command.
 *
 * @param new The new child process node.
 * @param argv The command line arguments.
 * @param index The index of the command in argv.
 * @return The split command arguments.
 */
char	**ft_handle_cmd_diff(t_child **new, char **argv, int index)
{
	char	*trim;
	char	**split;

	trim = NULL;
	split = NULL;
	(*new)->cmd_path = argv[index];
	trim = ft_substr(argv[index], 9, ft_strlen(argv[index]));
	if (trim != NULL)
		split = ft_split(trim, ' ');
	if (trim)
		free(trim);
	return (split);
}

void	ft_print_error(t_pipex *pipex, t_child *child, int signal)
{
	if (pipex->status == 127 && child->cmd_path != NULL)
	{
		ft_putstr_fd("/usr/bin/", 2);
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (pipex->status == 127)
	{
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (pipex->status == 126)
	{
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (signal == 0)
		ft_putstr_fd("Error: while allocation (parsing_cmd)\n", 2);
	else if (signal == 12)
	{
		ft_closing_files(pipex, pipex->nb_cmd);
		ft_free_everything(pipex);
	}
}
