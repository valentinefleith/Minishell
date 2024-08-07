/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:42:24 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/07 13:34:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_in_stack(t_token **stack, int type)
{
	t_token	*node;

	if (!stack)
		return (NULL);
	node = *stack;
	while (node)
	{
		if (node->type == type)
			return (node);
		node = node->next;
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
					*state = 1; // si word go to 1
				else
					*state = 2; // si token redir go to 2 
				return (shift);
			}
			start++;
		}
		list = list->next;
	}
	return (error);
}

void	replace_type(t_token **stack, int old_type, int new_type)
{
	t_token	*node;

	node = find_in_stack(stack, old_type);
	node->type = new_type;
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