/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/20 17:24:47 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"
# include "libft.h"
# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef enum e_operation
{
	shift,
	reduce,
	accept,
	error,
}					t_operation;

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
	command = 100,
	cmd_name,
	cmd_suffix,
	cmd_prefix,
	program,
	cmd,
}					t_grammar;

typedef enum e_token_type
{
	WORD,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	ASSIGNMENT,
	UNDEFINED,
}					t_token_type;

typedef struct s_token
{
	char			*data;
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
// t_btree		*parser(t_token **input_tokens, t_token *stack);
t_btree  *parser(t_token **input_tokens, t_btree *tree);
t_operation	parsing_table(int *state, t_operation *rules, t_token **stack, t_token *input);
void		get_grammar_rules(t_operation *tab_rules);
t_token		*find_in_stack(t_token **stack, int type);
void		reduce_operation(t_token **stack, t_btree **tree, int *state);
void		shift_operation(t_token **stack, t_token **input);
void		error_operation(t_token **stack, t_token **input);
void		replace_type(t_token **stack, int old_type, int new_type);
void		concatenate_cmd_to_param(t_token **stack);
void		monitor_stack(t_token **stack, t_btree **tree);

/* Debug */
void	debug_print_stack(t_token **stack_p);
void	debug_print_input(t_token **input_p);

#endif
