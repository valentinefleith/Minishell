/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:39:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 12:06:21 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_no_env(char *cmd_name)
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

static char	*get_path_env(char *cmd_name, char **paths)
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

static char	*find_right_path(char **paths, t_cmd cmd)
{
	char	*executable_path;

	if (ft_strchr(cmd.cmd_and_args[0], '/') || !paths)
		executable_path = get_path_no_env(cmd.cmd_and_args[0]);
	else
		executable_path = get_path_env(cmd.cmd_and_args[0], paths);
	if (!executable_path)
	{
		if (cmd.cmd_and_args[0] && ft_strnstr(cmd.cmd_and_args[0], "./", 2))
		{
			ft_free_tab(cmd.cmd_and_args);
			free_and_exit(paths, 126);
		}
		ft_free_tab(cmd.cmd_and_args);
		free_and_exit(paths, 127);
	}
	return (executable_path);
}

t_cmd	parse_cmd_executable(char *buffer, char **paths)
{
	t_cmd	cmd;
	char **cmd_and_args;

	cmd_and_args = ft_split(buffer, ' ');
	if (!cmd_and_args)
		free_and_exit(paths, 2);
	if (!cmd_and_args[0])
	{
		ft_putendl_fd("bash: cmd not found:", 2);
		ft_free_tab(cmd_and_args);
		free_and_exit(paths, 2);
	}
	//cmd.cmd_and_args = handle_quotes(cmd_and_args);
	cmd.cmd_and_args = cmd_and_args;
	if (!cmd.cmd_and_args)
		free_and_exit(paths, 2);
	cmd.exec_path = find_right_path(paths, cmd);
	return (cmd);
}
