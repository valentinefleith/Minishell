/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:32:39 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/12 16:57:47 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack_debug(t_liste **stack, t_token *input)
{
	t_liste *tmp;
	t_token	*temp;

	tmp = *stack;
	if (!tmp)
		printf("STACK = null\n");
	else
		printf("STACK = ");
	while (tmp != NULL)
	{
		if (tmp->data == command)
			printf("command ");
		else if (tmp->data == 0)
			printf("WORD ");
		else if (tmp->data == cmd_name)
			printf("cmd_name ");
		else if (tmp->data == program)
			printf("program ");
		else if (tmp->data == cmd_suffix)
			printf("cmd_suffix ");
		tmp = tmp->next;
	}
	printf("\n");
	temp = input;
	if (!temp)
		printf("INPUT = null\n");
	else
		printf("INPUT = ");
	while (temp != NULL)
	{
		if (temp->type == WORD)
			printf("WORD ");
		// else if (temp->type == INPUT)
		// 	printf("cmd_name");
		// else if (temp->type == program)
		// 	printf("program");
		// else if (temp->type == cmd_suffix)
		// 	printf("cmd_suffix");
		temp = temp->next;
	}
	printf("\n");
}

void	lr_parsing(t_token **input_token)
{
	t_token		*input;
	t_liste		*stack;
	t_action	action;
	int			state;

	if (!*(input_token))
		return ;
	input = *input_token;
	stack = NULL;
	action = shift;
	state = 0;
	// while (action != accept)
	for (int i = 0; i < 6; i++)
	{
		printf("state = %d\n", state);
		action = get_action(&state, stack, input);
		if (action == shift)
			action_shift(&stack, &input);
		else if (action == reduce)
			action_reduce(&stack, &state);
		else if (action == error)
			printf("Error: with the parsing table\n");
			// handle_parsing_error();
		printf("action = %d\n", action);
		print_stack_debug(&stack, input);
	}
}

t_action	get_action(int *state, t_liste *stack, t_token *input)
{
	if (*state == 0)
	{
		if (!stack)
		{
			*state = 1;
			return (shift);
		}
		else if (find_in_stack(&stack, program) == true)
			*state = 2;
		else if (find_in_stack(&stack, command) == true)
			*state = 3;
		else if (find_in_stack(&stack, cmd_name) == true)
			*state = 4;
	}
	if (*state == 1)
		return (reduce);
	if (*state == 2)
	{
		*state = 5;
		return (shift);
	}
	if (*state == 3)
		return (reduce);
	if (*state == 4)
	{
		if (input->type == WORD)
		{
			*state = 6;
			return (shift);
		}
		if (find_in_stack(&stack, cmd_suffix) == true)
			*state = 7;
		else if (find_in_stack(&stack, cmd_name) == true 
			&& find_in_stack(&stack, cmd_suffix) == true)
			return (reduce);
	}
	if (*state == 5)
		return (accept);
	if (*state == 6)
		return (reduce);
	if (*state == 7)
	{
		if (input->type == WORD)
		{
			*state = 8;
			return (shift);
		}
		return (reduce);
	}
	if (*state == 8)
		return (reduce);
	return (error);
}

void	action_reduce(t_liste **stack, int *state_pt)
{
	t_liste	*reduce_node;
	int		state;

	state = *state_pt;
	reduce_node = *stack;
	if (state == 1)
	{
		while (reduce_node->next != NULL)
		{
			if (reduce_node->data != WORD)
				reduce_node = reduce_node->next;
		}
		reduce_node->data = cmd_name;
	}
	// if (state == 3)
	// 	// change command to program
	// if (state == 4 || state == 7)
	// 	// change cmd_name & cmd_suffix to command
	// if (state == 6 || state == 8)
	// 	// change WORD to cmd_suffix if no cmd_suffix already in the liste
	*state_pt = 0;
}

bool	find_in_stack(t_liste **stack, t_rules type)
{
	t_liste *current;
	
	if (!*(stack))
		return (false);
	current = *stack;
	while (current != NULL)
	{
		if (current->data == type)
			return (true);
		current = current->next;
	}
	return (false);
}

void	action_shift(t_liste **stack, t_token **input)
{
	t_liste	*new_stack;
	t_liste	*new_node;

	new_stack = *stack;
	new_node = NULL;
	new_node = malloc(sizeof(t_liste));
	if (!new_node)
	{
		printf("Error: while allocation during shift action\n");
		return ;
	}
	new_node->data = (t_rules)(*input)->type;
	new_node->next = NULL;
	if (!new_stack)
		new_stack = new_node;
	else
	{
		new_stack = get_last_node(stack);
		new_stack->next = new_node;
	}
	*input = (*input)->next;
	*stack = new_stack;
}

t_liste	*get_last_node(t_liste **stack)
{
	t_liste *tmp;

	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
