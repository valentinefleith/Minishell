/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:38:18 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/01 15:33:08 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env_list *env_list)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (env_list)
	{
		seeking = ft_strncmp(env_list->name, "PATH", 4);
		if (!seeking)
			break ;
		env_list = env_list->next;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(env_list->data + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
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

	if (!command_name)
		return (NULL);
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
