/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/09 17:08:23 by vafleith         ###   ########.fr       */
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
t_token  *parser(t_token **input_tokens)
{
	t_token		*tokens;
	t_token		*stack;
	t_token		*output;
	int			action;
	int			state;

	if (!(*input_tokens))
		return (NULL);
	tokens = *input_tokens;
	stack = NULL;
	output = malloc(sizeof(t_token *));
	output = NULL;
	action = go_to;
	state = 0;
	while (action != accept)
	{
		action = parsing_table(&stack, tokens, &state);
		if (action == shift)
			shift_action(&stack, &tokens);
		else if (action == reduce)
			reduce_action(&stack, &tokens, &output, &state);
		else if (action == error)
			error_action(&stack, &tokens);
		debug_parser(&stack, &tokens, state, action);
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

   /* if (find_in_stack(stack, CMD_SUFFIX))*/
		/*cat_tokens_type(stack, CMD_NAME, CMD_SUFFIX);*/
	/*eltokens_type(stack, CMD_NAME, CMD_NAME);*/
	new = NULL;
	while (*stack)
	{
		new = malloc(sizeof(t_token));
		new->type = (*stack)->type;
		new->arg = (*stack)->arg;
		new->next = NULL;
		tokens_add_back(output, new);
		*stack = (*stack)->next;
	}
	*stack = ft_free_tokens(stack);
}

/**
 *	Handles errors during parsing.
 */
void	error_action(t_token **stack, t_token **tokens)
{
	printf("Error: with the tokens list, do not fit with the parsing table\n");
	// debug_print_stack(*stack, "STACK");
	// debug_print_input(tokens);
	ft_free_tokens(tokens);
	ft_free_tokens(stack);
	exit(EXIT_FAILURE);
}

static int	get_arg_size(t_token *stack)
{
	int	i;

	i = 1;
	while (stack && stack->type == WORD)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

void	reduce_cmd_name(t_token **stack, t_token **tokens)
{
	t_token *cmd;
	int		nb_arg;
	int		i;

	cmd = find_in_stack(stack, WORD);
	nb_arg = get_arg_size(*tokens);
	if (nb_arg == 0)
		return ;
	cmd->arg = malloc(sizeof(char *) * nb_arg + 1);
	if (!cmd->arg)
		return ;
	cmd->arg[0] = ft_strdup(cmd->data);
	i = 1;
	cmd->arg[nb_arg] = 0;
	while (cmd->arg[i++])
		cmd->arg[i] = NULL;
	if (!cmd->arg[0])
	{
		ft_free_tab(cmd->arg);
		return;
	}
	replace_type(stack, WORD, CMD_NAME);
}
