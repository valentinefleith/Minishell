/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:29:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/01 15:01:33 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_redirection(t_btree *tree, t_shell *shell, int fd, int type)
{
	char	*filename;

	filename = NULL;
	filename = find_redirection(tree->right, shell, filename, type);
	if (filename)
	{
		close_fd(&fd);
		type = last_redirection(tree->right, &type, filename);
		fd = open_file(filename, type);
		if (fd == -1)
		{
			free_process(shell);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

char	*find_redirection(t_btree *tree, t_shell *shell, char *filename,
		int target)
{
	int	redir;
	int	fd;

	if (!tree || !tree->item)
		return (filename);
	fd = -1;
	redir = which_redirection_type(tree->item[0]);
	if (redir != HEREDOC)
		fd = open_file(tree->item[1], redir);
	if (fd != -1 && check_file_access(tree->item[1], redir) != -1)
		close_fd(&fd);
	else
		return (exit_child_process(shell, EXIT_FAILURE), NULL);
	if (redir == HEREDOC && target == INPUT)
		filename = "here_doc";
	else if (redir == INPUT && target == INPUT)
		filename = tree->item[1];
	else if ((redir == OUTPUT || redir == APPEND) && target == OUTPUT)
		filename = tree->item[1];
	if (tree->right != NULL)
		return (find_redirection(tree->right, shell, filename, target));
	return (filename);
}

int	which_redirection_type(char *operator)
{
	size_t	len;

	if (!operator)
		return (-1);
	len = ft_strlen(operator);
	if (!ft_strncmp(operator, "<<", 2) && len == 2)
		return (HEREDOC);
	else if (!ft_strncmp(operator, "<", 1) && len == 1)
		return (INPUT);
	else if (!ft_strncmp(operator, ">>", 2) && len == 2)
		return (APPEND);
	else if (!ft_strncmp(operator, ">", 1) && len == 1)
		return (OUTPUT);
	return (-1);
}

int	open_file(char *filename, int file_type)
{
	int	fd;

	fd = -1;
	if (file_type == INPUT)
		fd = open(filename, O_RDONLY);
	if (file_type == APPEND || file_type == HEREDOC)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file_type == OUTPUT)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

int	last_redirection(t_btree *tree, int *type, char *name)
{
	size_t	len;
	int		is_type;

	if (!tree || !tree->item[0] || !tree->item[1])
		return (*type);
	is_type = which_redirection_type(tree->item[0]);
	len = ft_strlen(tree->item[1]);
	if (ft_strlen(name) == len && !ft_strncmp(tree->item[1], name, len))
		*type = is_type;
	if (tree->right != NULL)
		return (last_redirection(tree->right, type, name));
	return (*type);
}
