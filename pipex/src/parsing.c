/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:22:55 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/31 15:37:16 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * Parses the command line arguments and creates a 
 * linked list of child processes.
 *
 * @param pipex The pipex structure.
 * @param argv The command line arguments.
 * @param j The starting index of the command arguments.
 * @param i The current index of the command arguments.
 */
void	ft_parsing_cmd(t_pipex *pipex, char **argv, int j, int i)
{
	t_child	*new;

	while ((i - j) != pipex->nb_arg)
	{
		new = NULL;
		new = malloc(sizeof(t_child));
		if (!new)
			ft_putstr_fd("Error: while allocation(parsing_data)\n", 2);
		new->index = i - j;
		new->pid = -1;
		new->executable = 0;
		new->cmd_path = NULL;
		if (ft_strnstr(argv[i], "/usr/bin/", ft_strlen(argv[i])) != NULL)
			new->cmd = ft_handle_diff(&new, argv, i);
		else if (ft_strnstr(argv[i], "./", ft_strlen(argv[i])) != NULL)
		{
			new->executable = 1;
			new->cmd = ft_split(argv[i], ' ');
		}
		else
			new->cmd = ft_split(argv[i], ' ');
		new->path = ft_parsing_path(pipex->env);
		ft_add_back(&pipex->child, new);
		i++;
	}
}

/**
 * Parses the PATH environment variable and returns an double array.
 *
 * @param env The environment variable array.
 * @return An array extracted from the PATH variable.
 */
char	**ft_parsing_path(char **env)
{
	char	**path;
	char	*str;
	char	*new;
	int		i;

	i = 0;
	str = NULL;
	new = NULL;
	if (!env)
		return (NULL);
	while (ft_strncmp(env[i], "PATH=", 5) != 0 && env[i] != NULL)
		++i;
	str = ft_strjoin(env[i], "/");
	new = ft_substr(str, 5, ft_strlen(str));
	path = ft_split(new, ':');
	if (str)
		free(str);
	if (new)
		free(new);
	return (path);
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
			pipex->status = 1;
			return ;
		}
		count--;
		i++;
	}
}

/**
 * This function is for parsing file descriptors(fd).
 * It allocates memory for the `fd` array based on the number of commands.
 * Each file descriptor is initially set to -1.
 *
 * @param pipex - A pointer to the `t_pipex` structure.
 */
void	ft_parsing_fd(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	pipex->fd = malloc(sizeof(int *) * (pipex->nb_arg));
	if (!pipex->fd)
	{
		ft_putstr_fd("Error: while allocation (fd)\n", 2);
		return ;
	}
	while (i != pipex->nb_arg)
	{
		pipex->fd[i] = malloc(sizeof(int) * 2);
		if (!pipex->fd)
			return ;
		j = 0;
		while (j != 2)
		{
			pipex->fd[i][j] = -1;
			j++;
		}
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
char	**ft_handle_diff(t_child **new, char **argv, int index)
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
