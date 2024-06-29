/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:39:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 15:30:52 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parse_cmd_executable(char *buffer, char **paths)
{
	char **cmd;
	cmd = ft_split(buffer, ' ');
	if (!cmd)
		free_and_exit(paths);
	cmd_path = find_right_path(paths, cmd);
	
}
