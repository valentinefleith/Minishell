/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/09 17:52:54 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 * Parses the input tokens and builds an output (linked list).
 * @input_tokens: The list of input tokens to be parsed.
 *
 * This function performs actions such as shift, reduce, and error
 * according on the current state and tokens (parsing_table).
 */
t_token  *parser(t_token *tokens)
{
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
			stack = error_action(stack, tokens, &state);
	}
	return (output);
}

/**
 * Builds the output token list from the stack.
 *
 * This function concatenates tokens of specific types from the stack and
 * adds them to the output token list. It also frees the stack after processing.
 */
void	build_output(t_token **stack, t_token **output)
{
	t_token	*new;
	t_token	*save;

	new = NULL;
	save = *stack;
	while (*stack)
	{
		new = copy_token(*stack, new);
		tokens_add_back(output, new);
		*stack = (*stack)->next;
	}
	*stack = save;
	while (*stack)
	{
		save = (*stack)->next;
		if (*stack)
			free(*stack);
		*stack = save;
	}
}

/**
 *	Handles errors during parsing.
 */
t_token	*error_action(t_token *stack, t_token *token_list, int *state)
{
	t_token	*token;
	
	token = get_last_token(stack);
	if (token_list)
		printf("%s\n", token_list->data);
	if (!ft_strncmp(stack->data, "<", 1) && ft_strlen(stack->data) == 1
		&& !ft_strncmp(token->data, ">", 1) && ft_strlen(token->data) == 1)
		printf("bash: syntax error near unexpected token 'newline'\n");
	else if (find_in_loop(token, state, INPUT, APPEND + 1) != error && !stack->next)
		printf("bash: syntax error near unexpected token 'newline'\n");
	// else if (stack && token 
	// 	&& find_in_loop(token, state, INPUT, APPEND + 1) != error
	// 	&& find_in_loop(token, state, INPUT, APPEND + 1) != error)
	// 	printf("bash: syntax error near unexpected token '%s%s'\n", stack->data, token->data);
	else
		printf("bash: syntax error near unexpected token '%s'\n", token->data);
	stack = ft_free_tokens(&stack);
	*state = -1;
	return (stack);
}
