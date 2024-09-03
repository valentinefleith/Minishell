/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:29:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/29 12:31:22 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_redirection(t_btree *tree, t_shell *shell, int index)
{
	char	*filename;
	
	ft_putstr_fd("before redirection = \n", 2);
	debug_exec(tree, shell);
	shell->fd_in = STDIN_FILENO;
	if (index != 0)
		shell->fd_in = shell->pipe_fd[index - 1][0];
	if (tree->right && tree->right->type == REDIR)
	{
		filename = find_input(tree->right, shell, NULL);
		// ft_putstr_fd("\nfilename intput =", 2);
		// 	if (filename == NULL)
		// 	ft_putstr_fd("NULL", 2);
		// else
		// 	ft_putstr_fd(filename, 2);
		// ft_putstr_fd("\n", 2);
		if (filename)
			shell->fd_in = open_file(filename, INPUT);
	}
	ft_putstr_fd("\n nb_cmd - 1 =", 2);
	ft_putnbr_fd(shell->nb_cmd - 1, 2);
	ft_putstr_fd("\n index =", 2);
	ft_putnbr_fd(index, 2);
	ft_putstr_fd("\n", 2);
	shell->fd_out = STDOUT_FILENO;
	if (index != shell->nb_cmd - 1)
		shell->fd_out = shell->pipe_fd[index][1];
	ft_putstr_fd("\n value of pipe =", 2);
	ft_putnbr_fd(shell->pipe_fd[index][1], 2);
	ft_putstr_fd("\n", 2);
	if (tree->right && tree->right->type == REDIR)
	{
		filename = find_output(tree->right, shell, NULL);
		// ft_putstr_fd("\nfilename output =", 2);
		// 	if (filename == NULL)
		// 	ft_putstr_fd("NULL", 2);
		// else
		// 	ft_putstr_fd(filename, 2);
		// ft_putstr_fd("\n", 2);
		if (filename)
			shell->fd_out = open_file(filename, OUTPUT);
	}
	ft_putstr_fd("after redirection = \n", 2);
	debug_exec(tree, shell);
	if (shell->fd_in == -1 || shell->fd_out == -1)
		return (1);
	// dup2(shell->fd_in, STDIN_FILENO);
	// dup2(shell->fd_out, STDOUT_FILENO);
	return (0);
}

char	*find_input(t_btree *tree, t_shell *shell, char *name)
{
	if (!tree || !tree->item)
		return (name);
	if (tree->type == REDIR && !ft_strncmp(tree->item[0], "<<", 2))
		name = parsing_heredoc(tree->item[1], ft_strlen(tree->item[1]));
	if (tree->type == REDIR && !ft_strncmp(tree->item[0], "<", 1))
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
	// ft_putstr_fd("\nfilename  IN output =", 2);
	// if (name == NULL)
	// 	ft_putstr_fd("NULL", 2);
	// else
	// 	ft_putstr_fd(name, 2);
	// ft_putstr_fd("\n", 2);
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

int	**creating_pipe(t_btree *root)
{
	int	nb_pipe;
	int	**fd;
	int	i;

	nb_pipe = 0;
	nb_pipe = count_pipe(root, &nb_pipe);
	if (nb_pipe <= 0)
		return (NULL);
	fd = malloc(sizeof(int *) * nb_pipe);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < nb_pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (NULL);
		fd[i][0] = -1;
		fd[i][1] = -1;
		if (pipe(fd[i]) == -1)
			return (ft_putstr_fd("Error: pipe\n", 2), NULL);
		i++;
	}
	return (fd);
}

int	close_fd(t_shell *shell)
{
	int	count;

	count = 0;
	while (count < (shell->nb_cmd - 1))
	{
		if (shell->pipe_fd[count][0] != -1)
		{
			if (close(shell->pipe_fd[count][0] == -1))
				return (perror("pipe_fd[0]"), -1);
			shell->pipe_fd[count][0] = -1;
		}
		if (shell->pipe_fd[count][1] != -1)
		{
			if (close(shell->pipe_fd[count][1] == -1))
				return (perror("pipe_fd[1]"), -1);
			shell->pipe_fd[count][1] = -1;
		}
		count++;
	}
	return (close_files(shell->fd_in, shell->fd_out));
}

int	close_files(int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
			return (perror("failed closing fd input"), -1);
		fd_in = -1;
	}
	if (fd_out != -1)
	{
		if (close(fd_out) == -1)
			return (perror("failed closing fd output"), -1);
		fd_out = -1;
	}
	return (0);
}

int	check_file_access(char *filename, int file_type)
{
	if (!filename)
		return (1);
	if (file_type == INPUT && access(filename, F_OK) != -1)
	{
		if (access(filename, R_OK) == -1)
			return (perror(filename), 1);
	}
	else if (file_type == INPUT)
		return (perror(filename), 1);
	if (file_type == OUTPUT && access(filename, W_OK) == -1)
		return (perror(filename), 1);
	if (file_type == HEREDOC)
	{
		if (access("here_doc", F_OK) == -1)
			unlink("here_doc");
		if (access("here_doc", F_OK) != -1 && access("here_doc", W_OK) == -1)
			return (perror("here_doc"), 1);
	}
	return (0);
}

int	checking_cmd_access(char *path)
{
	if (access(path, F_OK) == -1)
		return (127);
	if (access(path, X_OK) == -1)
		return (126);
	return (0);
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
		input = get_next_line(STDIN_FILENO);
		if (ft_strnstr(input, limit, len) && !ft_strncmp(&input[len], "\n", 1))
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
	return ("here_doc");
}
