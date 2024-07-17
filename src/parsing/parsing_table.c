/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:56:12 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/16 14:27:57 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack_debug(t_token **stack, t_token *input)
{
	t_token	*tmp;
	t_token	*temp;

	tmp = *stack;
	if (!tmp)
		printf("STACK = null\n");
	else
		printf("STACK = ");
	while (tmp != NULL)
	{
		if (tmp->grammar_type == command)
			printf("command ");
		else if (tmp->grammar_type == 0)
			printf("WORD ");
		else if (tmp->grammar_type == cmd_name)
			printf("cmd_name ");
		else if (tmp->grammar_type == program)
			printf("program ");
		else if (tmp->grammar_type == cmd_suffix)
			printf("cmd_suffix ");
		printf("(%s) ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
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

t_token	*parsing_grammar_rules(t_token **input_tokens, t_token *stack)
{
	t_action	rules[8];
	t_token		*input;
	t_action	action;
	int			state;

	input = *input_tokens;
	if (!input)
		return (NULL);
	get_grammar_rules(rules);
	action = shift;
	state = 1;
	action_shift(&stack, &input);
	while (action != accept)
	{
		// printf("state = %d\n", state);
		action = parsing_table(&state, rules, stack, input);
		// printf("action = %d\n", action);
		// printf("state = %d\n", state);
		if (action == shift)
			action_shift(&stack, &input);
		else if (action == reduce)
			action_reduce(&stack, &state);
		else if (action == error)
			printf("Error: with the parsing table\n");
		// print_stack_debug(&stack, input);
	}
	return (stack);
}

void	action_reduce(t_token **stack, int *state)
{
	t_token	*node;
	
	if (!stack)
		return ;
	if (*state == 1 || *state == 6)
	{
		node = find_in_stack(stack, (t_grammar)WORD);
		node->grammar_type = cmd_name;
	}
	if (*state == 3)
	{
		node = find_in_stack(stack, command);
		node->grammar_type = program;
	}
	if (*state == 4 || *state == 7)
	{
		node = find_in_stack(stack, cmd_name);
		node->grammar_type = command;
	}
	if (*state == 8)
		node = find_in_stack(stack, cmd_suffix);
	if (*state == 6)
		node->grammar_type = cmd_suffix;
	// if (*state == 4 || *state == 7 || *state == 8)
	// 	node->next = NULL;
	*state = 0;
}

void	action_shift(t_token **stack, t_token **input)
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
	new_node->grammar_type = (t_grammar)(*input)->type;
	new_node->next = NULL;
	tokens_add_back(stack, new_node);
	*input = (*input)->next;
}

t_action	parsing_table(int *state, t_action *rules, t_token *stack, t_token *input)
{
	if (*state == 0)
	{
		if (find_in_stack(&stack, program) != NULL && !input)
			*state = 2;
		else if (find_in_stack(&stack, command) != NULL)
			*state = 3;
		else if (find_in_stack(&stack, cmd_name) != NULL)
			*state = 4;
	}
	if (*state == 4 && input != NULL && input->type == WORD)
	{
		*state = 6;
		return (shift);
	}
	else if (*state == 4 && find_in_stack(&stack, cmd_suffix) != NULL)
		*state = 7;
	if (*state == 7 && input != NULL && input->type == WORD)
	{
		*state = 8;
		return (shift);
	}
	return (rules[*state]);
}

void	get_grammar_rules(t_action *tab_rules)
{
	tab_rules[0] =  error;
	tab_rules[1] =  reduce;
	tab_rules[2] =  accept;
	tab_rules[3] =  reduce;
	tab_rules[4] =  reduce;
	tab_rules[5] =  error;
	tab_rules[6] =  reduce;
	tab_rules[7] =  reduce;
	tab_rules[8] =  reduce;
}
