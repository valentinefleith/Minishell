/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:33:09 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/20 14:00:36 by luvallee         ###   ########.fr       */
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

char	*get_path_env(char *cmd_name, char **paths)
{
	char	*cmd_attempt;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_attempt = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!cmd_attempt)
			return (NULL);
		if (access(cmd_attempt, F_OK) == 0)
		{
			if (access(cmd_attempt, X_OK) == 0)
				return (cmd_attempt);
			permission_denied(cmd_name);
		}
		free(cmd_attempt);
		i++;
	}
	return (get_path_no_env(cmd_name));
}

char	*get_full_cmd_path(char *command_name, char **paths)
{
	char	*executable_path;

	if (ft_strchr(command_name, '/') || !paths)
		executable_path = get_path_no_env(command_name);
	else
		executable_path = get_path_env(command_name, paths);
	return (executable_path);
}

char	*get_path_no_env(char *cmd_name)
{
	if (access(cmd_name, F_OK) != 0)
	{
		if (ft_strchr(cmd_name, '/'))
			no_such_file(cmd_name);
		else
			cmd_not_found(cmd_name);
		return (NULL);
	}
	if (access(cmd_name, X_OK) != 0)
	{
		permission_denied(cmd_name);
		return (NULL);
	}
	return (ft_strdup(cmd_name));
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

int	checking_cmd_access(char *cmd_name, char *path)
{
	if (!path)
	{
		if (cmd_name && ft_strnstr(cmd_name, "./", 2))
			return(126);
		return(127);
	}
	if (access(path, F_OK) == -1)
		return (127);
	if (access(path, X_OK) == -1)
		return (126);
	return (0);
}
