/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/13 16:21:05 by luvallee         ###   ########.fr       */
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
	CMD_NAME = 104,
	CMD_PREFIX,
	REDIR,
	CMD_SUFFIX,
	PIPELINE,
	COMMAND,
	CMD,
}					t_grammar;

typedef enum e_token_type
{
	WORD,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	UNDEFINED,
}					t_token_type;

typedef struct s_token
{
	char			*data;
	char			**arg;
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

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

/************************ Lexing *********************************************/

t_token				*tokenize_cmdline(char *buffer);
bool				check_quote_status(bool inside_quotes,
						bool inside_opposite_quotes);
void				fill_token_types(t_token *tokens);

t_token				*create_node(char *buffer, int size);
void				tokens_add_back(t_token **tokens, t_token *new);

t_token				*ft_free_tokens(t_token **tokens);
t_token				*ft_free_top_node(t_token **tokens);
void				ft_free_token_node(t_token **token);


t_token				*get_last_token(t_token *tokens);
t_token				*get_first_token(t_token *tokens);
t_token				*get_last_pipe(t_token *tokens);

/************************ Parsing table **************************************/

t_token				*shift_action(t_token *stack, t_token **tokens);
t_token				*reduce_action(t_token *stack, t_token *tokens, 
						t_token **output, int *state);
void				cat_tokens(t_token *stack, int type);
void				init_stack_arg(t_token *stack, t_token *tokens, int type);
void				build_output(t_token **stack, t_token **output);

t_action			parsing_table(t_token *stack, t_token *tokens, int *state);
t_action			state_zero(t_token *stack, t_token *tokens, int *state);
t_action			state_four(t_token *stack, t_token *tokens, int *state);
t_action			state_five(t_token *stack, t_token *tokens, int *state);
t_action			state_tens(t_token *stack, t_token *tokens, int *state);

t_token				*parser(t_token *input_tokens);
void				error_action(t_token **stack, t_token **tokens);

t_token				*find_in_stack(t_token *stack, int type);
t_action			find_in_loop(t_token *list, int *state, int start, int end);
void				replace_type(t_token *stack, int old_type, int new_type);
int					find_redir_type(t_token *stack);
int					count_nb_arg(t_token *stack);

/************************ Binary Tree ****************************************/

t_btree				**create_ast(t_token *tokens);

t_btree				*btree_create_node(char *data, int type);
t_btree				*btree_create_cmd(void);

void				btree_free(t_btree *tree);

bool				btree_is_leaf(t_btree *tree);
bool				btree_is_empty(t_btree *tree);

/************************ Env ************************************************/

t_env				*build_env_list(t_env *env, char **src_env);
void				print_env_list(t_env *env);


void				add_env_list(t_env **list, t_env *new);
t_env				*free_env_list(t_env **list);

/************************ Debug **********************************************/

void				ft_print_token_types(t_token *tokens);
void				print_single_token_type(t_token_type type);
void				ft_print_lexing(t_token *tokens);

void				debug_parser(t_token *stack, t_token *input, int state,
						int ope);
void				debug_print_stack(t_token *stack, char *list);
void				debug_print_input(t_token **input_p);

void				print_structure(t_btree *root, int level);

#endif
