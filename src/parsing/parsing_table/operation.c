/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/31 19:31:47 by vafleith         ###   ########.fr       */
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
		return (error_action(stack, state));
	shifted = malloc(sizeof(t_token));
	if (!shifted)
		return (stack);
	shifted->data = ft_strdup((*tokens)->data);
	shifted->arg = NULL;
	shifted->type = (*tokens)->type;
	shifted->next = NULL;
	tokens_add_back(&stack, shifted);
	save = (*tokens)->next;
	ft_free_token_node(tokens);
	*tokens = save;
	return (stack);
}

/**
 * Reduces the stack based on the current state and modifies the output.
 */
t_token	*reduce_action(t_token *stack, t_token *tokens, t_token **output, int *state)
{
	if (*state == 1)
	{
		replace_type(stack, WORD, CMD);
		init_arg(stack, tokens, state, CMD);
	}
	if (*state == 3)
		cat_tokens(stack, state, CMD);
	if (*state == 6)
	{
		replace_type(stack, INPUT, REDIR);
		init_arg(stack, tokens, state, REDIR);
		cat_tokens(stack, state, REDIR);
	}
	else if (*state >= 4 && *state <= 15)
	{
		build_output(&stack, output);
		if (!tokens)
		{	
			*state = 7;
			return (stack);
		}
	}
	if (*state != -1)
		*state = 0;
	return (stack);
}

void	init_arg(t_token *stack, t_token *tokens, int *state, int type)
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
		return ;
	}
	i = 1;
	while (i < nb_arg + 1)
	{
		node->arg[i] = NULL;
		i++;
	}
	(void)state;
	// checking_cmd_syntax(node, state);
}

void	cat_tokens(t_token *stack, int *state, int type)
{
	t_token	*token;
	//size_t	len;
	int		pos;
	
	token = find_last_type(stack, type);
	if (!token || !token->arg || !token->next || token->next->type != WORD)
	{
		error_action(token, state);
		return ;
	}
	//len = ft_strlen(token->next->data);
	pos = 1;
	while (token->arg[pos])
		pos++;
	//if ((token->next->data[0] == SINGLE_QUOTE 
	//	|| token->next->data[0] == DOUBLE_QUOTE)
	//	&& (token->next->data[len - 1] == SINGLE_QUOTE 
	//	|| token->next->data[len - 1] == DOUBLE_QUOTE))
	//	token->arg[pos] = ft_substr(token->next->data, 1, len - 1);
	//else
	token->arg[pos] = ft_strdup(token->next->data);
	if (!token->arg[pos])
		return (ft_free_tab(token->arg));
	ft_free_token_node(&token->next);
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
