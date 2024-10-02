/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/02 12:25:21 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 * This function performs a "shift" action in a parser.
 * It moves the first token from the tokens list to the stack.
 * The new node's data and type are copied from the first token in the tokens
 * list. The new node is then added to the end of the stack.
 * The first token in the tokens list is removed and freed.
 */
t_token	*shift_action(t_token *stack, t_token **tokens, int *state)
{
	t_token	*shifted;
	t_token	*save;

	if (!tokens || !*tokens)
		return (error_action(stack, *tokens, NULL, state));
	shifted = malloc(sizeof(t_token));
	if (!shifted)
		return (stack);
	shifted->data = ft_strdup((*tokens)->data);
	shifted->arg = NULL;
	shifted->type = (*tokens)->type;
	shifted->next = NULL;
	tokens_add_back(&stack, shifted);
	save = (*tokens)->next;
	ft_free_token_node(*tokens);
	*tokens = save;
	return (stack);
}

/**
 * This function performs a "reduce" action in the parser. It modifies
 * the stack according to the value of the state. The modifications can
 * be concatenation of tokens, replacing the type of a token, or building
 * the final output (a token-list).
 */
t_token	*reduce_action(t_token *stack, t_token *tokens, t_token **output,
		int *state)
{
	if (*state == 1)
	{
		replace_type(stack, WORD, CMD);
		init_arg(stack, tokens, CMD);
	}
	if (*state == 3)
		cat_tokens(stack, state, CMD);
	if (*state == 6)
	{
		if (replace_type(stack, HEREDOC, REDIR) == -1)
			return (error_action(stack, tokens, output, state));
		init_arg(stack, tokens, REDIR);
		cat_tokens(stack, state, REDIR);
	}
	else if (*state >= 4 && *state <= 15)
	{
		build_output(&stack, output);
		if (!tokens)
			*state = 7;
	}
	if (*state != -1 && *state != 7)
		*state = 0;
	return (stack);
}

void	cat_tokens(t_token *stack, int *state, int type)
{
	t_token	*token;
	int		pos;

	token = find_last_type(stack, type);
	if (token->next && token->next->type != WORD)
	{
		special_input_arg(token);
		return ;
	}
	if (!token || !token->arg || !token->next)
	{
		error_action(token, NULL, NULL, state);
		return ;
	}
	pos = 1;
	while (token->arg[pos])
		pos++;
	token->arg[pos] = ft_strdup(token->next->data);
	if (!token->arg[pos])
		return (ft_free_tab(token->arg));
	ft_free_token_node(token->next);
	token->next = NULL;
}

/**
 * This function
 */
void	init_arg(t_token *stack, t_token *tokens, int type)
{
	t_token	*node;
	int		nb_arg;
	int		i;

	node = find_last_type(stack, type);
	if (type == CMD)
		nb_arg = count_nb_arg(tokens) + 1;
	else
		nb_arg = 2;
	node->arg = malloc(sizeof(char *) * (nb_arg + 1));
	if (!node->arg)
		return ;
	node->arg[0] = ft_strdup(node->data);
	if (!node->arg[0])
	{
		ft_free_tab(node->arg);
		node->arg[0] = NULL;
		return ;
	}
	i = 1;
	while (i < nb_arg + 1)
	{
		node->arg[i] = NULL;
		i++;
	}
}

int	replace_type(t_token *stack, int old_type, int new_type)
{
	t_token	*node;

	node = NULL;
	if (!stack)
		return (-1);
	if (new_type == REDIR && stack && stack->type == old_type)
		node = stack;
	else if (new_type == REDIR && stack && stack->type == APPEND)
		node = find_in_stack(stack, APPEND);
	else if (new_type == CMD)
		node = find_in_stack(stack, WORD);
	while (!node)
	{
		node = find_in_stack(stack, old_type);
		old_type++;
	}
	if (new_type == REDIR && node && node->next && (node->next->type != WORD
			|| node->next->type == PIPE))
		return (-1);
	node->type = new_type;
	return (0);
}
