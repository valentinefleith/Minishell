/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:17:40 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/02 22:05:08 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"
# include "env.h"
# include "libft.h"
# include "minishell.h"
# include <stdbool.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

typedef enum e_builtin	t_builtin;

typedef enum e_action
{
	shift,
	reduce,
	accept,
	error,
	go_to,
}						t_action;

typedef enum e_grammar_rules
{
	CMD = 100,
	REDIR,
	COMMAND,
	PIPELINE,
}						t_grammar;

typedef enum e_token_type
{
	WORD,
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT,
	PIPE,
	UNDEFINED,
}						t_token_type;

typedef struct s_token
{
	char				*data;
	char				**arg;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_btree
{
	int					type;
	struct s_btree		*left;
	struct s_btree		*right;
	char				**item;
}						t_btree;

/*** LEXING ******************************************************************/

t_token					*tokenize_cmdline(char *buffer, t_env *envs);

t_token					*create_node(char *buffer, int size);
void					tokens_add_back(t_token **tokens, t_token *new);
t_token					*quote_error(t_token *tokens);
t_token					*ft_free_tokens(t_token *tokens);
t_token					*ft_free_top_node(t_token **tokens);
void					ft_free_token_node(t_token *token);

t_token					*get_last_token(t_token *tokens);
t_token					*get_first_token(t_token *tokens);
t_token					*get_last_pipe(t_token *tokens);

void					perform_var_expansion(t_token *tokens, t_env *envs);
char					*remove_quotes(char *data);
int						get_len_varname(char *data, int index);
t_env_list				*find_target_variable(t_env_list *env_list, char *data,
							int index);
void					update_quote_status(bool *in_single_quotes,
							bool *in_double_quotes, char c);
int						copy_beginning_data(int index, char *dest, char *src);

/*** PARSER ******************************************************************/

t_token					*shift_action(t_token *stack, t_token **tokens,
							int *state);
t_token					*reduce_action(t_token *stack, t_token *tokens,
							t_token **output, int *state);
void					cat_tokens(t_token *stack, int *state, int type);
void					init_arg(t_token *stack, t_token *tokens, int type);
int						replace_type(t_token *stack, int old_type,
							int new_type);

int						special_input_arg(t_token *stack_token);
t_token					*get_second_last_token(t_token *tokens);
t_token					*find_last_type(t_token *stack, int type);
int						count_nb_arg(t_token *stack);

t_token					*parser(t_token *tokens, t_env_list *env_list);
void					build_output(t_token **stack, t_token **output);
char					*parsing_heredoc(char *limit, int len);

t_action				parsing_table(t_token *stack, t_token *tokens,
							int *state);
t_action				state_zero(t_token *stack, t_token *tokens, int *state);
t_action				state_four(t_token *stack, t_token *tokens, int *state);
t_action				state_five(t_token *stack, t_token *tokens, int *state);
t_action				state_tens(t_token *stack, t_token *tokens, int *state);

t_token					*find_in_stack(t_token *stack, int type);
t_action				find_in_loop(t_token *list, int *state, int start,
							int end);
t_token					*copy_token(t_token *stack, t_token *new);

/*** BINARY TREE *************************************************************/

t_btree					*create_ast(t_token *tokens);

t_btree					*btree_create_node(char **data, int type);
t_btree					*btree_create_cmd(void);

void					btree_free(t_btree *tree);

bool					btree_is_leaf(t_btree *tree);
bool					btree_is_empty(t_btree *tree);

/*** DEBUG *******************************************************************/

void					ft_print_token_types(t_token *tokens);
void					print_single_token_type(t_token_type type);
void					ft_print_lexing(t_token *tokens);

void					print_structure(t_btree *root, int level);
void					btree_print_details(t_btree *root, int level);

#endif
