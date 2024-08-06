/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/06 17:23:27 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"
# include "libft.h"
# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef enum e_action
{
	shift,
	reduce,
	accept,
	error,
	go_to,
}					t_action;

typedef struct s_cmd
{
	t_builtin		builtin_type;
	char			*exec_path;
	char			**cmd_and_args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef enum e_grammar_rules
{
	cmd_name = 104,
	cmd_prefix, // 105
	redirection, // 106
	io_file, // 107
	cmd_suffix, // 108
	pipeline, // 109
	command, // 110
	cmd,
	program,
}					t_grammar;

typedef enum e_token_type
{
	WORD, // 0
	INPUT, // 1
	HEREDOC, // 2
	OUTPUT, // 3
	APPEND, // 4 
	PIPE, // 5
	ASSIGNMENT,
	UNDEFINED,
}					t_token_type;

typedef struct s_token
{
	char			**data;
	char			**test;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_btree
{
	int				type;
	struct s_btree	*left;
	struct s_btree	*right;
	char			*item;
}					t_btree;

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
void ft_print_lexing(t_token *tokens);
void ft_print_token_types(t_token *tokens);
void print_single_token_type(t_token_type tokens);

/* binary tree utils */
// t_btree				*btree_create_node(t_token *item);
t_btree				*btree_create_node(char *data, int type);
t_btree 			*btree_create_cmd(void);
bool				btree_is_empty(t_btree *tree);
bool				btree_is_leaf(t_btree *tree);
void				btree_free(t_btree *tree);
void print_structure(t_btree *root, int level);
t_btree *create_ast(t_token *tokens);


/* Parsing table */
// t_btree  *parser(t_token **input_tokens, t_btree *tree);
t_token  **parser(t_token **input_tokens);
char	**cat_tokens_arg(t_token *node, int add);
int	get_cat_size(t_token *stack, int type);
void	build_output(t_token **stack, t_token **output);
int	count_nodes(t_token *stack);

// t_action	parsing_table(int *state, t_action *rules, t_token **stack, t_token *input);
t_action	parsing_table(t_token **stack, t_token *input, int *state);
t_action	state_zero(t_token **stack, t_token *input, int *state);
t_action	state_four(t_token **stack, t_token *input, int *state);
t_action	state_five(t_token **stack, t_token *input, int *state);
t_action	state_tens(t_token **stack, t_token *input, int *state);


void		get_grammar_rules(t_action *tab_rules);
t_token		*find_in_stack(t_token **stack, int type);
void		shift_action(t_token **stack, t_token **input);
void		error_action(t_token **stack, t_token **input);
void		replace_type(t_token **stack, int old_type, int new_type);

void	reduce_action(t_token **stack, t_token **output, int *state);
void	reduce_type_redirection(t_token **stack);
void	cat_tokens_type(t_token **stack, int target, int old_type);


void		concatenate_cmd_to_param(t_token **stack);
void		monitor_stack(t_token **stack, t_btree **tree);
t_action	find_in_loop(t_token *list, int *state, int i, int count);
/* Debug */
void	debug_print_stack(t_token *stack_p, char *list);
void	debug_print_input(t_token **input_p);
void	debug_parser(t_token **stack, t_token **input, int state, int ope);

#endif