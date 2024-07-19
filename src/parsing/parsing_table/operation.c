/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/19 13:06:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_operation(t_token **stack, int *state)
{
	t_token	*node;
	
	if (!stack)
		return ;
	if (*state == 1 || *state == 6)
	{
		node = find_in_stack(stack, (t_grammar)WORD);
		node->type = cmd_name;
	}
	if (*state == 3)
	{
		node = find_in_stack(stack, command);
		node->type = program;
	}
	if (*state == 4 || *state == 7)
	{
		node = find_in_stack(stack, cmd_name);
		node->type = command;
	}
	if (*state == 8)
		node = find_in_stack(stack, cmd_suffix);
	if (*state == 6)
		node->type = cmd_suffix;
	// if (*state == 4 || *state == 7 || *state == 8)
	// 	node->next = NULL;
	*state = 0;
}

void	shift_operation(t_token **stack, t_token **input)
{
	t_token	*new_node;

	if (!input)
		return ;
	new_node = NULL;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		printf("Error: while allocation during shift action\n");
		return ;
	}
	new_node->data = (*input)->data;
	new_node->type = (t_grammar)(*input)->type;
	new_node->next = NULL;
	tokens_add_back(stack, new_node);
	*input = (*input)->next;
}

void	error_operation(int state, t_token **stack, t_token **input)
{
	printf("Error: with the input, do not fit with the parsing table\n");
	debug_print_stack(stack);
	debug_print_input(input);
	ft_free_tokens(input);
	ft_free_tokens(stack);
	exit(EXIT_FAILURE);
}