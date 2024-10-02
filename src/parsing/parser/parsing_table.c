/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:56:12 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/02 12:28:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Determines the next action based on the current state and stack or tokens.
 * @stack: The stack of tokens being processed.
 * @tokens: The token in input.
 * @state: The current state of the parser.
 *
 * This function evaluates the current state and token to decide the next action
 * for the parser. It returns an action such as shift, reduce, accept, or error.
 */
t_action	parsing_table(t_token *stack, t_token *tokens, int *state)
{
	if (*state == 7)
		return (accept);
	if (*state == 0)
		return (state_zero(stack, tokens, state));
	if (*state == 2 && tokens && tokens->type == WORD)
	{
		*state = 6;
		return (shift);
	}
	if (*state == 4)
		return (state_four(stack, tokens, state));
	if (*state == 5)
		return (state_five(stack, tokens, state));
	if (*state == 9 && tokens && tokens->type == PIPE)
	{
		*state = 9;
		return (shift);
	}
	if (*state == 11 || *state == 14)
		return (state_tens(stack, tokens, state));
	if (*state == 1 || *state == 3 || *state == 6 || *state == 8 || *state == 9
		|| *state == 10 || *state == 12 || *state == 13 || *state == 15)
		return (reduce);
	return (error);
}

/**
 *  Handles the parser's actions when in state 0.
 */
t_action	state_zero(t_token *stack, t_token *tokens, int *state)
{
	if (find_in_stack(stack, CMD))
		*state = 4;
	else if (find_in_stack(stack, REDIR))
		*state = 5;
	if (stack && stack->type == PIPE)
		return (error);
	if (*state != 0)
		return (go_to);
	if (find_in_loop(tokens, state, WORD, OUTPUT + 1) == shift)
		return (shift);
	if (!stack && tokens && tokens->type == PIPE)
		return (shift);
	return (error);
}

t_action	state_four(t_token *stack, t_token *tokens, int *state)
{
	if (find_in_loop(tokens, state, HEREDOC, OUTPUT + 1) == shift)
		return (shift);
	else if (tokens && tokens->type == WORD)
	{
		*state = 3;
		return (shift);
	}
	else if (find_in_stack(stack, REDIR))
	{
		*state = 9;
		return (go_to);
	}
	else if (tokens && tokens->type == PIPE)
	{
		if (!tokens->next)
			return (error);
		if (tokens->next && tokens->next->type == PIPE)
			return (error);
		*state = 8;
		return (shift);
	}
	return (reduce);
}

t_action	state_five(t_token *stack, t_token *tokens, int *state)
{
	if (find_in_stack(stack, CMD))
		*state = 11;
	else if (find_in_loop(tokens, state, WORD, WORD + 1) == shift)
		return (shift);
	else if (tokens && tokens->type == PIPE)
	{
		*state = 10;
		return (shift);
	}
	if (*state != 5)
		return (go_to);
	return (reduce);
}

t_action	state_tens(t_token *stack, t_token *tokens, int *state)
{
	if (*state == 11 && find_in_stack(stack, REDIR))
		*state = 14;
	else if (*state == 11 && find_in_loop(tokens, state, INPUT, OUTPUT
			+ 1) == shift)
		return (shift);
	else if (*state == 11 && tokens && tokens->type == PIPE)
	{
		*state = 13;
		return (shift);
	}
	else if (*state == 11)
		return (reduce);
	if (*state == 14 && tokens && tokens->type == PIPE)
	{
		*state = 15;
		return (shift);
	}
	else if (*state == 14)
		return (reduce);
	return (error);
}
