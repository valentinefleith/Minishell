/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:29:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/06 18:08:54 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_redirection(t_btree *tree, t_shell *shell, int fd, int type)
{
	char *filename;
	
	filename = NULL;
	if (type == INPUT)
		filename = find_input(tree->right, shell, filename);
	else if (type == OUTPUT)
		filename = find_output(tree->right, shell, filename);
	if (filename)
	{
		close_fd(&fd);
		fd = open_file(filename, type);
		if (fd == -1)
		{
			free_process(shell, tree);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

char *find_input(t_btree *tree, t_shell *shell, char *name)
{
	if (!tree || !tree->item)
		return (name);
	if (tree->type == REDIR && !ft_strncmp(tree->item[0], "<<", 2))
		name = parsing_heredoc(tree->item[1], ft_strlen(tree->item[1]));
	else if (tree->type == REDIR && !ft_strncmp(tree->item[0], "<", 1))
	{
		if (check_file_access(tree->item[1], INPUT) != 1)
			name = tree->item[1];
		else
			error_execution(shell, tree, 1);
	}
	if (tree->right != NULL)
		find_input(tree->right, shell, name);
	return (name);
}

char	*find_output(t_btree *tree, t_shell *shell, char *name)
{
	if (!tree || !tree->item)
		return (name);
	if (tree->type == REDIR && (!ft_strncmp(tree->item[0], ">>", 2)
		|| !ft_strncmp(tree->item[0], ">", 1)))
	{
		open_file(tree->item[1], OUTPUT);
		if (check_file_access(tree->item[1], OUTPUT) != 1)
			name = tree->item[1];
		else
			error_execution(shell, tree, 1);
	}
	if (tree->right != NULL)
		find_output(tree->right, shell, name);
	return (name);
}

int	open_file(char *filename, int file_type)
{
	int	fd;

	fd = -1;
	if (file_type == INPUT)
		fd = open(filename, O_RDONLY);
	if (file_type == OUTPUT)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file_type == HEREDOC)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

char	*parsing_heredoc(char *limit, int len)
{
	char	*input;
	int		fd;
	
	if (!limit || check_file_access("here_doc", HEREDOC) != 0)
		return (NULL);
	fd = open("here_doc", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			ft_putstr_fd("\nbash: here-document delimited by end-of-file", 2);
			break ;
		}
		else if (ft_strnstr(input, limit, len) && !ft_strncmp(&input[len], "\n", 1))
			break ;
		else
			write(fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	return (close(fd), "here_doc");
}
