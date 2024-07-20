/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/20 17:30:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_operation(t_token **stack, t_btree **tree, int *state)
{
	if (!stack)
		*state = 0;
	if (*state == 1)
		replace_type(stack, WORD, cmd_name);
	if (*state == 3)
	{
		monitor_stack(stack, tree);
		replace_type(stack, command, program);
	}
	if (*state == 4 || *state == 7)
		replace_type(stack, cmd_name, command);
	if (*state == 8)
		replace_type(stack, cmd_suffix, cmd_suffix);
	if (*state == 6)
		replace_type(stack, WORD, cmd_suffix);
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
	new_node->type = (*input)->type;
	new_node->next = NULL;
	tokens_add_back(stack, new_node);
	*input = (*input)->next;
}

void	error_operation(t_token **stack, t_token **input)
{
	printf("Error: with the input, do not fit with the parsing table\n");
	debug_print_stack(stack);
	debug_print_input(input);
	ft_free_tokens(input);
	ft_free_tokens(stack);
	exit(EXIT_FAILURE);
}

void	replace_type(t_token **stack, int old_type, int new_type)
{
	t_token	*node;

	node = find_in_stack(stack, old_type);
	node->type = new_type;
}