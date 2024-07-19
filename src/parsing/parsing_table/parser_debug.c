/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:40:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/19 13:15:48 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_stack(t_token **stack_p)
{
	t_token	*stack;

	if (!stack_p || !(*stack_p))
	{
		printf("STACK = NULL\n");
		return ;
	}
	else
		printf("STACK = ");
	stack = *stack_p;
	while (stack)
	{
		if (stack->type == command)
			printf("command ");
		else if (stack->type == WORD)
			printf("WORD ");
		else if (stack->type == cmd_name)
			printf("cmd_name ");
		else if (stack->type == program)
			printf("program ");
		else if (stack->type == cmd_suffix)
			printf("cmd_suffix ");
		printf("(%s) ", stack->data);
		stack = stack->next;
	}
	printf("\n");
}

void	debug_print_input(t_token **input_p)
{
	t_token	*input;

	if (!input_p || !(*input_p))
	{
		printf("INPUT = NULL\n");
		return ;
	}
	else
		printf("INPUT = ");
	input = *input_p;
	while (input)
	{
		if (input->type == INPUT)
			printf("INPUT ");
		else if (input->type == WORD)
			printf("WORD ");
		else if (input->type == HEREDOC)
			printf("HEREDOC ");
		else if (input->type == OUTPUT)
			printf("OUTPUT ");
		else if (input->type == PIPE)
			printf("PIPE ");
		else if (input->type == ASSIGNMENT)
			printf("ASSIGNMENT ");
		else if (input->type == UNDEFINED)
			printf("UNDEFINED ");
		input = input->next;
	}
	printf("\n");
}