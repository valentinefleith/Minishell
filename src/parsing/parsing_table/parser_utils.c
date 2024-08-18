/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:42:24 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/15 15:20:27 by luvallee         ###   ########.fr       */
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

void	replace_type(t_token *stack, int old_type, int new_type)
{
	t_token	*node;
	
	node = find_in_stack(stack, old_type);
	while (!node)
	{
		node = find_in_stack(stack, old_type);
		old_type++;
	}
	node->type = new_type;
}

int	count_nb_arg(t_token *stack)
{
	int	nb;

	nb = 1;
	whnble (stack && stack->type == WORD)
	{
		nb++;
		stack = stack->next;
	}
	return (nb);
}
