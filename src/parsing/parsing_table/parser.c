/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/06 14:55:21 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"

t_token  **parser(t_token **input_tokens)
{
	t_token		*tokens;
	t_token		*stack;
	t_token		**output;
	int			action;
	int			state;

	if (!(*input_tokens))
		return (NULL);
	tokens = *input_tokens;
	stack = NULL;
	output = malloc(sizeof(t_token *));
	*output = NULL;
	action = go_to;
	state = 0;
	while (action != accept)
	{
		action = parsing_table(&stack, tokens, &state);
		if (action == shift)
			shift_action(&stack, &tokens);
		else if (action == reduce)
			reduce_action(&stack, output, &state);
		else if (action == error)
			error_action(&stack, &tokens);
		debug_parser(&stack, &tokens, state, action);
	}
	return (output);
}

char	**cat_tokens_arg(t_token **stack, int target, int adding)
{
	char	**concatenation;
	t_token *node;
	int 	i;

	concatenation = malloc(get_cat_size(*stack, adding) * sizeof(char *) + 1);
	if (!concatenation)
		return (NULL);
	node = find_in_stack(stack, target);
	i = 0;
	while (node)
	{
		if (node->type == adding)
		{
			concatenation[i] = ft_strdup((char *)node->data);
			if (!concatenation[i])
			{
				ft_free_tab(concatenation);
				return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	concatenation[i] = 0;
	return (concatenation);
}

int	get_cat_size(t_token *stack, int type)
{
	int	nb;

	nb = 1;
	while (stack)
	{
		if (stack->type == type)
			nb++;
		stack = stack->next;
	}
	return (nb);
}

int	count_nodes(t_token *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

void	build_output(t_token **stack, t_token **output)
{
	t_token	*new;

	if (find_in_stack(stack, cmd_suffix))
		cat_tokens_type(stack, cmd_name, cmd_suffix);
	new= NULL;
	while (*stack)
	{
		new = malloc(sizeof(t_token));
		new->type = (*stack)->type;
		new->data = (*stack)->data;
		new->next = NULL;
		tokens_add_back(output, new);
		*stack = (*stack)->next;
	}
	stack = ft_free_tokens(stack);
}
