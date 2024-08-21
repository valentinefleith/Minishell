/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:40:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/14 19:45:53 by luvallee         ###   ########.fr       */
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
		if (stack->type == COMMAND)
			printf("command ");
		else if (stack->type == WORD)
			printf("WORD ");
		else if (stack->type == REDIR)
			printf("REDIR ");
		else if (stack->type == CMD)
			printf("CMD ");
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
		i = 0;
		if (stack->arg && stack->arg[i])
		{
			if (!stack->arg[i])
				break ;
			while (stack->arg[i])
			{
				printf("%s ", stack->arg[i]);
				i++;
			}
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
		else if (input->type == UNDEFINED)
			printf("UNDEFINED ");
		input = input->next;
	}
	printf("\n");
}

void	debug_parser(t_token *stack, t_token *input, int state, int ope)
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
	debug_print_stack(input, "INPUT");
	debug_print_stack(stack, "STACK");
	printf("                                      \n");
}
