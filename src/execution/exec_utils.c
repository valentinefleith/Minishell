/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:33:09 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/01 12:39:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_btree *tree, int *nb_cmd)
{
	if (!tree)
		return (*nb_cmd);
	if (tree->type == COMMAND)
		*nb_cmd += 1;
	if (tree->left && tree->left->type == COMMAND)
		*nb_cmd += 1;
	return (count_cmd(tree->right, nb_cmd));
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
	if ((file_type == OUTPUT || file_type == APPEND) 
		&& access(filename, W_OK) == -1)
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

int	checking_cmd_access(char *cmd_name, char *path)
{
	if (!path)
	{
		if (cmd_name && ft_strnstr(cmd_name, "./", 2))
			return(126);
		return(127);
	}
	if (path && !ft_strncmp(cmd_name, "..", 2) && ft_strlen(cmd_name) == 2)
		return (cmd_not_found(cmd_name), 127);
	if (access(path, F_OK) == -1)
		return (127);
	if (access(path, X_OK) == -1)
		return (126);
	return (0);
}
