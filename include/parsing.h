/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/12 13:53:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"
# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef enum e_action
{
	shift,
	reduce,
	accept,
	error,
}	t_action;

typedef struct s_cmd
{
	t_builtin		builtin_type;
	char			*exec_path;
	char			**cmd_and_args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef enum e_rules
{
	command = 100,
	cmd_name,
	cmd_suffix,
	program,
}					t_rules;

typedef enum e_token_type
{
	WORD,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	FILENAME,
	UNDEFINED,
}					t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	t_rules			rule;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_liste
{
	t_rules			data;
	struct s_liste *next;
}	t_liste;

t_cmd				parse_user_prompt(char *buffer, char **env);
t_cmd				parse_cmd_executable(char *buffer, char **paths);
void				no_such_file(char *filename);
void				cmd_not_found(char *cmd_name);
void				permission_denied(char *name);
char				**handle_quotes(char **cmd_and_args);
// t_cmd	**get_whole_pipeline(char *buffer, char **env);
t_token				**tokenize_cmdline(char *buffer);
t_token				*create_node(char *buffer, int size);
t_token				*get_last_token(t_token *tokens);
void				tokens_add_back(t_token **tokens, t_token *new);
/* lexing_utils */
// static t_token_type find_token_type(char *data, t_token *tokens);
void				fill_token_types(t_token *tokens);

/* Test LR parsing */

void	lr_parsing(t_token **input_token);
t_action	get_action(int *state_p, t_liste *stack, t_token *input);
void	action_reduce(t_liste **stack, int *state);
bool	find_in_stack(t_liste **stack, t_rules type);
void	action_shift(t_liste **stack, t_token **input);
t_liste	*get_last_node(t_liste **stack);

#endif
