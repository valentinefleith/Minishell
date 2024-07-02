/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/02 15:58:17 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_user_prompt(char *buffer, char **env)
{
	(void)buffer;
	(void)env;
	t_input input;
	char 	**line_input;

	line_input = ft_split(buffer, ' ');
	parse_builtin(line_input, &input);
	if (input.builtin != NONE)
		execute_builtin(input.builtin, &input);
	// char **cmd;
	// if (is_builtin)
	// 		cmd = parse_builtin(buffer);
	// else
	// 		cmd = parse_cmd_executable(buffer, env);
	free(line_input);
}

