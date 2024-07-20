/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/20 13:42:11 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// printf("-------------- OPE ");
	// if (ope == shift)
	// 	printf("shift ");
	// if (ope == reduce)
	// 	printf("reduce ");
	// if (ope == accept)
	// 	printf("accept ");
	// printf("--------------\n");
	debug_print_input(input);
	debug_print_stack(stack);
}

t_token  *parser(t_token **input_tokens, t_token *stack)
{
	t_token		*input;
	t_operation	rules[9];
	int			action;
	int			state;

	input = *input_tokens;
	if (!input)
		return (NULL);
	get_grammar_rules(rules);
	action = shift;
	state = 1;
	shift_operation(&stack, &input);
	while (action != accept)
	{
		action = parsing_table(&state, rules, &stack, input);
		if (action == shift)
			shift_operation(&stack, &input);
		else if (action == reduce)
			reduce_operation(&stack, &state);
		else if (action == error)
			error_operation(&stack, &input);
		debug_parser(&stack, &input, state, action);
	}
	return (stack);
}
