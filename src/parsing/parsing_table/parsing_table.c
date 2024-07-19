/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:56:12 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/19 14:22:29 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_grammar_rules(int *tab_rules)
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

int	parsing_table(int *state, int *rules, t_token *stack, t_token *input)
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
