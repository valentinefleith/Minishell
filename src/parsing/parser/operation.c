/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/30 11:22:15 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 *	This function performs a "shift" action in a parser.
 *   It moves the first token from the tokens list to the stack.

	*   The new node's data and type are copied from the first token in the tokens list.
 *   The new node is then added to the end of the stack.
 *   The first token in the tokens list is removed and freed.
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
 * Reduces the stack based on the current state and modifies the output.
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

static t_token	*get_second_last_token(t_token *tokens)
{
	t_token	*second_last;

	second_last = NULL;
	while (tokens)
	{
		if (tokens->next == NULL)
			return (second_last);
		else
			second_last = tokens;
		tokens = tokens->next;
	}
	return (second_last);
}

static int	special_input_arg(t_token *stack_token)
{
	t_token	*word_token;
	t_token	*last_token;
	int		pos;

	if (!stack_token)
		return (-1);
	word_token = find_last_type(stack_token, WORD);
	if (!word_token)
		return (1);
	pos = 1;
	while (stack_token->arg[pos])
		pos++;
	stack_token->arg[pos] = ft_strdup(word_token->data);
	if (!stack_token->arg[pos])
		return (ft_free_tab(stack_token->arg), -1);
	last_token = get_second_last_token(stack_token);
	ft_free_token_node(word_token);
	last_token->next = NULL;
	return (0);
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

t_token	*find_last_type(t_token *stack, int type)
{
	t_token	*last;

	if (!stack)
		return (NULL);
	last = NULL;
	while (stack)
	{
		if (stack->type == type)
			last = stack;
		stack = stack->next;
	}
	return (last);
}
