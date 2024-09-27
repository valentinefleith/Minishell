/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:42:24 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/27 16:00:27 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_in_stack(t_token *stack, int type)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->type == type)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

t_action	find_in_loop(t_token *list, int *state, int start, int end)
{
	while (list)
	{
		while (start < end)
		{
			if (list && list->type == start)
			{
				if (start == 0)
					*state = 1;
				else
					*state = 2;
				return (shift);
			}
			start++;
		}
		list = list->next;
	}
	return (error);
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
	if (new_type == REDIR && node && node->next
		&& (node->next->type != WORD || node->next->type == PIPE))
		return (-1);
	node->type = new_type;
	return (0);
}

t_token	*copy_token(t_token *stack, t_token *new)
{
	new = malloc(sizeof(t_token));
	if (!new)
	{
		printf("Error: while allocation\n");
		return (NULL);
	}
	new->type = stack->type;
	new->arg = stack->arg;
	new->data = stack->data;
	new->next = NULL;
	return (new);
}

// hope there is no conflict with the filename of a REDIR
int	count_nb_arg(t_token *stack)
{
	int	nb;

	nb = 0;
	while (stack && stack->type != PIPE)
	{
		if (stack->type == WORD)
			nb++;
		stack = stack->next;
	}
	return (nb);
}
