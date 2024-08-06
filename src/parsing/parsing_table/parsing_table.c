/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:56:12 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/06 17:47:35 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_action	parsing_table(t_token **stack, t_token *tokens, int *state)
{
	if (*state == 8 && tokens && tokens->type == PIPE)
	{
		*state = 0;
		return (shift);
	}
	if (*state == 0)
		return (state_zero(stack, tokens, state));
	if (*state == 2)
	{
		*state = 7;
		return (shift);
	}
	if (*state == 3 || (*state == 8 && !tokens))
		return (accept);
	if (*state == 4)
		return (state_four(stack, tokens, state));
	if (*state == 5)
		return (state_five(stack, tokens, state));
	if (*state == 10 || *state == 12)
		return (state_tens(stack, tokens, state));
	if (*state == 1 || *state == 6 || *state == 7 || *state == 9 
		|| *state == 11 || *state == 13 || *state == 14)
		return (reduce);
	return (error);
}

t_action	state_zero(t_token **stack, t_token *input, int *state)
{
	if (find_in_stack(stack, cmd_name))
		*state = 4;
	else if (find_in_stack(stack, cmd_prefix))
		*state = 5;
	else if (find_in_stack(stack, redirection))
		*state = 6;
	else if (find_in_loop(input, state, WORD, APPEND + 1) == shift)
		return (shift);
	return (go_to);
}

t_action	state_four(t_token **stack, t_token *tokens, int *state)
{
	if (find_in_loop(tokens, state, INPUT, APPEND + 1) == shift)
		return (shift);
	if (find_in_stack(stack, cmd_suffix))
		*state = 10;
	else if (find_in_stack(stack, redirection) && tokens)
		*state = 11;
	else if (tokens && tokens->type == WORD)
	{
		*state = 9;
		return (shift);
	}
	else if (!tokens || tokens->type == PIPE)
		*state = 10;
	return (go_to);
}

t_action	state_five(t_token **stack, t_token *tokens, int *state)
{
	if (find_in_stack(stack, cmd_name))
	{
		*state = 12;
		return (go_to);
	}
	else if (tokens && tokens->type == WORD)
	{
		*state = 1;
		return (shift);
	}
	return (error);
}

t_action	state_tens(t_token **stack, t_token *tokens, int *state)
{
	if (*state == 10 && tokens && tokens->type == WORD)
	{
		*state = 13;
		return (shift);
	}
	else if (*state == 10 && (!tokens || tokens->type == PIPE))
		return (reduce);
	if (*state == 12)
	{
		if (find_in_stack(stack, cmd_suffix))
			*state = 10;
		else if (find_in_stack(stack, redirection))
			*state = 11;
		if (*state != 12)
			return (go_to);
	}
	if (*state == 12 && tokens && tokens->type == WORD)
		*state = 9;
	else if (*state == 12)
		find_in_loop(tokens, state, INPUT, APPEND);
	return (shift);
}
// void	get_grammar_rules(t_action *tab_rules)
// {
// 	tab_rules[0] =  error;
// 	tab_rules[1] =  reduce;
// 	tab_rules[2] =  accept;
// 	tab_rules[3] =  reduce;
// 	tab_rules[4] =  reduce;
// 	tab_rules[5] =  error;
// 	tab_rules[6] =  reduce;
// 	tab_rules[7] =  reduce;
// 	tab_rules[8] =  reduce;
// 	tab_rules[9] =  error;
// 	tab_rules[10] = shift;
// }

// t_operation	parsing_table(int *state, t_operation *rules, t_token **stack, t_token *input)
// {
// 	if (*state == 0)
// 	{
// 		if (find_in_stack(stack, program) != NULL && !input)
// 			*state = 2;
// 		else if (find_in_stack(stack, command) != NULL)
// 			*state = 3;
// 		else if (find_in_stack(stack, cmd_name) != NULL)
// 			*state = 4;
// 	}
// 	if (*state == 4 && input != NULL && input->type == WORD)
// 	{
// 		*state = 6;
// 		return (shift);
// 	}
// 	else if (*state == 4 && find_in_stack(stack, cmd_suffix) != NULL)
// 		*state = 7;
// 	if (*state == 7 && input != NULL && input->type == WORD)
// 	{
// 		*state = 8;
// 		return (shift);
// 	}
// 	if (*state == 9)
// 		find_loop(&input, state, 1, 5);
// 	return (rules[*state]);
// }
