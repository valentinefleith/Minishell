/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:59:09 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/04 13:40:23 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * This function calls the necessary functions.
 *
 * @param pipex The pipex structure.
 * @param argv The command line arguments.
 */
void	ft_parsing(t_pipex *pipex, char **argv, int fd)
{
	if (pipex->here_doc.here == TRUE)
	{
		if (!argv[2] || !argv[2][0])
		{
			ft_putstr_fd("Error: missing delimiter\n", 2);
			exit(1);
		}
		else
			pipex->here_doc.limiter = argv[2];
		if (ft_checking_file_access(pipex, here_doc) != ERROR)
		{
			fd = open("here_doc", O_CREAT | O_WRONLY, 0644);
			if (fd == ERROR)
			{
				close(fd);
				exit(1);
			}
			ft_parsing_here_doc(pipex->here_doc.limiter, fd, NULL);
		}
	}
	if (pipex->here_doc.here == TRUE)
		ft_parsing_cmd(pipex, argv, 3, 3);
	else
		ft_parsing_cmd(pipex, argv, 2, 2);
	ft_parsing_fd(pipex);
}

/**
 * This function collects all lines of input that follow until it encounters
 * the (de)limiter and stores it in the input's file.
 *
 * @param pipex The pipex structure.
 * @param argv The command line arguments.
 */
void	ft_parsing_here_doc(char *lim, int fd, char *input)
{
	while (1)
	{
		input = get_next_line(0);
		if (ft_strnstr(input, lim, ft_strlen(lim)) != NULL
			&& ft_strncmp(&input[ft_strlen(lim)], "\n", 1) == 0)
			break ;
		else if (!input)
		{
			ft_putstr_fd("here-document delimited by end-of-file", 2);
			break ;
		}
		else
			write(fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	close(fd);
}

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

	while ((i - j) <= pipex->nb_cmd)
	{
		new = NULL;
		new = malloc(sizeof(t_child));
		if (!new)
			ft_print_error(pipex, NULL, 0);
		new->index = i - j;
		new->pid = -1;
		new->cmd_path = NULL;
		new->executable = 0;
		if (ft_strnstr(argv[i], "/usr/bin/", ft_strlen(argv[i])) != NULL)
			new->cmd = ft_handle_cmd_diff(&new, argv, i);
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
	char	*temp;
	int		i;

	i = 0;
	str = NULL;
	temp = NULL;
	if (!env)
		return (NULL);
	while (ft_strncmp(env[i], "PATH=", 5) != 0 && env[i] != NULL)
		++i;
	str = ft_strjoin(env[i], "/");
	temp = ft_substr(str, 5, ft_strlen(str));
	path = ft_split(temp, ':');
	if (str)
		free(str);
	if (temp)
		free(temp);
	return (path);
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
	pipex->fd = malloc(sizeof(int *) * (pipex->nb_cmd + 1));
	if (!pipex->fd)
	{
		ft_putstr_fd("Error: while allocation (fd)\n", 2);
		return ;
	}
	while (i != pipex->nb_cmd)
	{
		pipex->fd[i] = malloc(sizeof(int) * 3);
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
