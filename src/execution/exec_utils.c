/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:33:09 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/29 11:25:10 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_btree *tree, int *nb_pipe)
{
	if (!tree)
		return (*nb_pipe);
	if (tree->type == PIPE)
		*nb_pipe += 1;
	return (count_pipe(tree->right, nb_pipe));
}

int	count_cmd(t_btree *tree, int *nb_cmd)
{
	if (!tree)
		return (*nb_cmd);
	if (tree->type == COMMAND)
		*nb_cmd += 1;
	if (tree->left->type == COMMAND)
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
			//permission_denied(cmd_name);
		}
		free(cmd_attempt);
		i++;
	}
	return (get_path_no_env(cmd_name));
}

char *get_full_cmd_path(char *command_name, char **paths)
{
	char	*executable_path;

	if (ft_strchr(command_name, '/') || !paths)
		executable_path = get_path_no_env(command_name);
	else
		executable_path = get_path_env(command_name, paths);
	/*if (!executable_path)
	{
		if (command_name && ft_strnstr(command_name, "./", 2))
		{
			ft_free_tab(command_name);
			free_and_exit(paths, 126);
		}
		ft_free_tab(cmd.cmd_and_args);
		free_and_exit(paths, 127);
	}*/
	return (executable_path);
}

char	*get_path_no_env(char *cmd_name)
{
	/*if (access(cmd_name, F_OK) != 0)
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
	}*/
	return (ft_strdup(cmd_name));
}
