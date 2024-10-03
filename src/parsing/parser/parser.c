/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 11:48:57 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 * Parses the input tokens and builds an output (token list).
 * @input_tokens: The list of input tokens to be parsed.
 *
 * This function performs actions such as shift, reduce, and error
 * according on the current state and tokens (parsing_table).
 */
t_token	*parser(t_token *tokens, t_env_list *env_list)
{
	t_token	*stack;
	t_token	*output;
	int		action;
	int		state;

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
			stack = error_action(stack, tokens, &output, &state);
	}
	if (state == -1)
		update_exit_status(env_list, 2);
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
		if (new)
		{
			if (new->arg && new->arg[1] && !ft_strncmp(new->arg[0], "<<", 2)
				&& ft_strlen(new->arg[0]) == 2)
				parsing_heredoc(new->arg[1], ft_strlen(new->arg[1]));
		}
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

char	*parsing_heredoc(char *limit, int len)
{
	char	*input;
	int		fd;

	if (!limit || check_file_access("here_doc", HEREDOC) != 0)
		return (NULL);
	fd = open("here_doc", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		ft_putstr_fd("\e[32m> \e[0m", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			printf("\nbash: here-document delimited by end-of-file");
			break ;
		}
		if (ft_strnstr(input, limit, len) && !ft_strncmp(&input[len], "\n", 1))
			break ;
		else
			write(fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	return (close(fd), "here_doc");
}
