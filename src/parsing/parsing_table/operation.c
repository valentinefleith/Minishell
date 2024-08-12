/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/12 18:11:08 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "parsing.h"

/**
*	This function performs a "shift" action in a parser.
*   It moves the first token from the tokens list to the stack.
*   The new node's data and type are copied from the first token in the tokens list.
*   The new node is then added to the end of the stack.
*   The first token in the tokens list is removed and freed.
*/
t_token	*shift_action(t_token *stack, t_token **tokens)
{
	t_token	*shifted;
	t_token	*save;
	
	if (!tokens)
		return (stack);
	shifted = malloc(sizeof(t_token));
	if (!shifted)
		return (stack); // gerer l'erreur et free ce qu'il faut;
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
		replace_type(stack, WORD, CMD_NAME);
		init_stack_arg(stack, tokens, CMD_NAME);
	}
	if (*state == 6)
		replace_type(stack, REDIR, CMD_PREFIX);
	if (*state == 7)
	{
		replace_type(stack, find_redir_type(stack), REDIR);
		init_stack_arg(stack, tokens, REDIR);
		cat_tokens(stack, REDIR);
	}
	if (*state == 9 || *state == 13)
		cat_tokens(stack, CMD_NAME);
	if (*state == 10 || *state == 14)
	{
		build_output(&stack, output);
		*state = 8;
		return (NULL);
	}
	*state = 0;
	return (stack);
}

void	init_stack_arg(t_token *stack, t_token *tokens, int type)
{
	t_token	*node;
	int		nb_arg;
	int		i;
	
	node = find_in_stack(stack, type);
	if (type == CMD_NAME)
		nb_arg = count_nb_arg(tokens);
	else
		nb_arg = 2;
	node->arg = malloc(sizeof(char *) * nb_arg + 1);
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
		node->arg[i] = 0;
		i++;
	}
}

void	cat_tokens(t_token *stack, int type)
{
	t_token	*token;
	int		pos;
	
	token = find_in_stack(stack, type);
	if (!token)
		return ;
	pos = 1;
	while (token->arg[pos])
		pos++;
	token->arg[pos] = ft_strdup(token->next->data);
	if (!token->arg[pos])
		return (ft_free_tab(token->arg));
	ft_free_token_node(&token->next);
	token->next = NULL;
}

/**
 * Builds the output token list from the stack.
 *
 * This function concatenates tokens of specific types from the stack and
 * adds them to the output token list. It also frees the stack after processing.
 */
void	build_output(t_token **stack, t_token **output)
{
	t_token	*new;
	t_token	*save;

	new = NULL;
	save = *stack;
	while (*stack)
	{
		new = malloc(sizeof(t_token));
		new->type = (*stack)->type;
		new->arg = (*stack)->arg;
		new->data = (*stack)->data;
		new->next = NULL;
		tokens_add_back(output, new);
		*stack = (*stack)->next;
	}
	*stack = save;
	while (*stack)
	{
		save = (*stack)->next;
		if (*stack)
			free(*stack);
		*stack = save;
	}
}