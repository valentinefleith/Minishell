/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/30 19:59:24 by vafleith         ###   ########.fr       */
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

t_cmd parse_user_prompt(char *buffer, char **env)
{
	t_cmd cmd;
	char **paths;
	pid_t pid;


	paths = get_paths(env);
	pid = fork();
	if (pid == 0){
		cmd = parse_cmd_executable(buffer, paths);
		execute_command(cmd, env);
	}
	// if (is_builtin)
	// 		cmd = parse_builtin(buffer);
	// else
	// 		cmd = parse_cmd_executable(buffer, env);
	//ft_printf("%s\n", cmd.exec_path);
	//for (int i = 0; cmd.cmd_and_args[i]; i++)
	//{
	//	ft_printf("%s,", cmd.cmd_and_args[i]);
	//}
	//ft_printf("\n");
	return cmd;
}
