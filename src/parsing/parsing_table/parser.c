/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:10 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

/**
 * Parses the input tokens and builds an output (linked list).
 * @input_tokens: The list of input tokens to be parsed.
 *
 * This function performs actions such as shift, reduce, and error
 * according on the current state and tokens (parsing_table).
 */
t_token  *parser(t_token *tokens, t_env *env)
{
	(void)env;
	t_token		*stack;
	t_token		*output;
	int			action;
	int			state;

	if (!tokens)
		return (NULL);
	stack = NULL;
	output = NULL;
	action = go_to;
	state = 0;
	while (action != accept && state != -1)
	{
		action = parsing_table(stack, tokens, &state);
		if (action == shift)
			stack = shift_action(stack, &tokens, &state);
		else if (action == reduce)
			stack = reduce_action(stack, tokens, &output, &state);
		else if (action == error)
			stack = error_action(stack, &state);
		debug_parser(stack, tokens, state, action);
	}
	parsing_tokens_arg(output, env);
	return (output);
}

/**
 *	Handles errors during parsing.
 */
t_token	*error_action(t_token *stack, int *state)
{
	t_token	*token;
	
	token = get_last_token(stack);
	if (find_in_loop(token, state, INPUT, APPEND + 1) != error && !stack->next)
		printf("bash: syntax error near unexpected token 'newline'\n");
	else
		printf("bash: syntax error near unexpected token '%s'\n", token->data);
	stack = ft_free_tokens(&stack);
	*state = -1;
	return (stack);
}
