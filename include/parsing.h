/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 21:28:08 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cmd
{
	char			*exec_path;
	char			**cmd_and_args;
}					t_cmd;

t_cmd	parse_user_prompt(char *buffer, char **env);
t_cmd parse_cmd_executable(char *buffer, char **paths);
void	no_such_file(char *filename);
void	cmd_not_found(char *cmd_name);
void	permission_denied(char *name);

#endif
