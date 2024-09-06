/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/06 16:08:34 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"
# include "env.h"
# include "libft.h"
# include "minishell.h"
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
}							t_action;

typedef struct s_cmd
{
	t_builtin				builtin_type;
	char					*exec_path;
	char					**cmd_and_args;
	int						infile;
	int						outfile;
	struct s_cmd			*next;
}							t_cmd;

typedef enum e_grammar_rules
{
	CMD = 100,
	REDIR,
	COMMAND,
	PIPELINE,
}							t_grammar;

typedef enum e_token_type
{
	WORD,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	UNDEFINED,
}							t_token_type;

typedef struct s_token
{
	char					*data;
	char					**arg;
	int						type;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_btree
{
	int						type;
	struct s_btree			*left;
	struct s_btree			*right;
	char					**item;
}							t_btree;

typedef struct s_env_list	t_env_list;
typedef struct s_env		t_env;

/************************ Lexing *********************************************/

t_token						*tokenize_cmdline(char *buffer, t_env *envs);

t_token						*create_node(char *buffer, int size);
void						tokens_add_back(t_token **tokens, t_token *new);
t_token						*quote_error(t_token **tokens);
t_token						*ft_free_tokens(t_token **tokens);
t_token						*ft_free_top_node(t_token **tokens);
void						ft_free_token_node(t_token **token);

t_token						*get_last_token(t_token *tokens);
t_token						*get_first_token(t_token *tokens);
t_token						*get_last_pipe(t_token *tokens);

void						perform_var_expansion(t_token *tokens, t_env *envs);
char						*remove_quotes(char *data);

/************************ Parsing table **************************************/

t_token						*shift_action(t_token *stack, t_token **tokens,
								int *state);
t_token						*reduce_action(t_token *stack, t_token *tokens,
								t_token **output, int *state);
void						cat_tokens(t_token *stack, int *state, int type);
void						init_arg(t_token *stack, t_token *tokens, int type);
t_token						*find_last_type(t_token *stack, int type);

t_action					parsing_table(t_token *stack, t_token *tokens,
								int *state);
t_action					state_zero(t_token *stack, t_token *tokens,
								int *state);
t_action					state_four(t_token *stack, t_token *tokens,
								int *state);
t_action					state_five(t_token *stack, t_token *tokens,
								int *state);
t_action					state_tens(t_token *stack, t_token *tokens,
								int *state);

t_token  					*parser(t_token *tokens);
void						build_output(t_token **stack, t_token **output);
t_token						*error_action(t_token *stack, int *state);

t_token						*find_in_stack(t_token *stack, int type);
t_action					find_in_loop(t_token *list, int *state, int start,
								int end);
void						replace_type(t_token *stack, int old_type,
								int new_type);
int							count_nb_arg(t_token *stack);
t_token						*copy_token(t_token *stack, t_token *new);

void						parsing_env_var(t_token *output, t_env_list *env);
t_env_list					*search_env_var(t_env_list *env_list, char *arg);
char						*do_expansion_var(t_env_list *env, char *arg,
								char *new_arg);
char						*get_var_name(char *arg);
int							get_new_arg_len(t_env_list *env, char *arg);

/************************ Binary Tree ****************************************/

t_btree						*create_ast(t_token *tokens);

t_btree						*btree_create_node(char **data, int type);
t_btree						*btree_create_cmd(void);

void						btree_free(t_btree *tree);

bool						btree_is_leaf(t_btree *tree);
bool						btree_is_empty(t_btree *tree);

/************************ Debug **********************************************/

void						ft_print_token_types(t_token *tokens);
void						print_single_token_type(t_token_type type);
void						ft_print_lexing(t_token *tokens);

void						debug_parser(t_token *stack, t_token *input,
								int state, int ope);
void						debug_print_stack(t_token *stack, char *list);
void						debug_print_input(t_token **input_p);

void						print_structure(t_btree *root, int level);
void						btree_print_details(t_btree *root, int level);

#endif
