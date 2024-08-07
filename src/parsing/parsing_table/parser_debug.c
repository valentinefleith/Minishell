/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:40:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/07 12:42:14 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_stack(t_token *stack, char *list)
{
	if (!stack)
	{
		printf("%s = NULL\n", list);
		return ;
	}
	else
		printf("%s = ", list);
	int i = 0;
	while (stack)
	{
		if (stack->type == command)
			printf("command ");
		else if (stack->type == WORD)
			printf("WORD ");
		else if (stack->type == cmd_name)
			printf("cmd_name ");
		else if (stack->type == redirection)
			printf("redirection ");
		else if (stack->type == cmd_suffix)
			printf("cmd_suffix ");
		else if (stack->type == cmd_prefix)
			printf("cmd_prefix ");
		else if (stack->type == io_file)
			printf("io_file ");
		else if (stack->type == pipeline)
			printf("pipeline ");
		if (stack->type == INPUT)
			printf("INPUT ");
		else if (stack->type == HEREDOC)
			printf("HEREDOC ");
		else if (stack->type == OUTPUT)
			printf("OUTPUT ");
		else if (stack->type == PIPE)
			printf("PIPE ");
		else if (stack->type == APPEND)
			printf("APPEND ");
		else if (stack->type == UNDEFINED)
			printf("UNDEFINED ");
		printf("( ");
		while (stack->data[i])
		{
			if (!stack->data[i] || stack->data[i][0] == 0)
				break ;
			printf("%s ", stack->data[i]);
			i++;
		}
		printf(") ");
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

void	debug_parser(t_token **stack, t_token **input, int state, int ope)
{
	static int i = 0;
	
	i += 1;
	(void)ope;
	printf("                                      \n");
	printf("                                      \n");
	printf("-------------- etape %d --------------\n", i);
	printf("                                      \n");
	printf("-------------- STATE %d --------------\n", state);
	printf("                                      \n");
	// printf("-------------- ACTION ");
	// if (ope == shift)
	// 	printf("shift ");
	// if (ope == reduce)
	// 	printf("reduce ");
	// if (ope == accept)
	// 	printf("accept ");
	// printf("--------------\n");
	debug_print_stack(*input, "INPUT");
	debug_print_stack(*stack, "STACK");
	printf("                                      \n");
}