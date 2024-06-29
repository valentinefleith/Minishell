/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 15:52:11 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **env)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (*env)
	{
		seeking = ft_strncmp(*env, "PATH", 4);
		if (!seeking)
			break ;
		env++;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(*env + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
}

void parse_user_prompt(char *buffer, char **env)
{
	t_cmd cmd;
	char **paths;

	paths = get_paths(env);
	
	// if (is_builtin)
	// 		cmd = parse_builtin(buffer);
	// else
	// 		cmd = parse_cmd_executable(buffer, env);
	cmd = parse_cmd_executable(buffer, paths);
	ft_printf("%s\n", cmd.exec_path);
}
