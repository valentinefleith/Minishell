/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:14:01 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/09 15:13:57 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Closes the file descriptors stored in the `pipex` structure.
 *
 * @param pipex The pipex structure.
 * @param count The number of file descriptors to be closed.
 */
void	ft_closing_files(t_pipex *pipex, int count)
{
	int	i;
	int	j;

	i = 0;
	while (count--)
	{
		j = 0;
		while (j != 2)
		{
			if (pipex->fd[i][j] != -1)
			{
				if (close(pipex->fd[i][j]) == ERROR)
					ft_putstr_fd("\e[31mFail close fd\e[0m\n", 2);
				pipex->fd[i][j] = -1;
			}
			j++;
		}
		i++;
	}
	ft_closing_arg(pipex);
}

/**
 * Closes the file descriptors associated with input
 * and output files in the pipex struct.
 *
 * @param pipex A pointer to the pipex struct.
 */
void	ft_closing_arg(t_pipex *pipex)
{
	if (pipex->file_input != -1)
	{
		if (close(pipex->file_input) == ERROR)
			perror(pipex->infile);
		pipex->file_input = -1;
	}
	if (pipex->file_output != -1)
	{
		if (close(pipex->file_output) == ERROR)
			perror(pipex->outfile);
		pipex->file_output = -1;
	}
}

/* Free the content of a multidimensional tab */
void	ft_deleting_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL || tab[i] != 0)
	{
		if (tab[i])
			free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void	ft_deleting_fd(int **fd, int count)
{
	int	i;

	i = 0;
	while (count--)
	{
		if (fd[i])
			free(fd[i]);
		fd[i] = NULL;
		i++;
	}
	if (fd)
		free(fd);
	fd = NULL;
}

/* Delete the content of every node of the linked list*/
void	ft_deleting_list(t_child **child)
{
	t_child	*temp;

	if (!*child)
		return ;
	temp = *child;
	while (temp != NULL)
	{
		temp = (*child)->next;
		ft_deleting_tab((*child)->cmd);
		ft_deleting_tab((*child)->path);
		free(*child);
		*child = temp;
	}
}
