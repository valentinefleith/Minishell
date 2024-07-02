/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/02 14:19:10 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_cmd
{
	char			*exec_path;
	char			**cmd_and_args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				parse_user_prompt(char *buffer, char **env);
t_cmd				parse_cmd_executable(char *buffer, char **paths);
void				no_such_file(char *filename);
void				cmd_not_found(char *cmd_name);
void				permission_denied(char *name);
char				**handle_quotes(char **cmd_and_args);
t_cmd	**get_whole_pipeline(char *buffer, char **env);

#endif
