/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 15:30:50 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cmd
{
	char			*exec_path;
	char			**cmd_and_args;
	char 			**env;
}					t_cmd;

void	parse_user_prompt(char *buffer, char **env);

char **parse_cmd_executable(char *buffer, char **paths);

#endif
