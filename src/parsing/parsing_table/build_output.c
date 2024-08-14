/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:50 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/14 18:17:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Builds the output token list from the stack.
 *
 * This function concatenates tokens of specific types from the stack and
 * adds them to the output token list. It also frees the stack after processing.
 */
void	build_output(t_token **stack, t_token **output, int *state)
{
	t_token	*new;
	t_token	*save;

	new = NULL;
	save = *stack;
	(void)state;
	while (*stack)
	{
		new = copy_token(*stack, new);
		// if (check_cmd_syntax(new))
			tokens_add_back(output, new);
		// else
		// {
		// 	error_action(stack, state);
		// 	return ;
		// }
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

int	checking_cmd_syntax(t_token *new)
{
	int	i;
	
	if (new->type != CMD || !new->data)
		return (-1);
	while (new->data[i])
	{
		if (!ft_isalpha(new->data[i]))
			return (-1);
		i++;
	}
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