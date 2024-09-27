/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:25:35 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/23 14:53:40 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_msg_error(t_token *stack, t_token *tokens_list, int *state)
{
	t_token	*token;

	if (!stack)
		return ;
	token = get_last_token(stack);
	if (!token || !token->data || !stack->data)
		return ;
	if (!ft_strncmp(stack->data, "<", 1) && ft_strlen(stack->data) == 1
		&& !ft_strncmp(token->data, ">", 1) && ft_strlen(token->data) == 1)
		printf("bash: syntax error near unexpected token 'newline'\n");
	else if (find_in_loop(token, state, HEREDOC, OUTPUT + 1) != error
		&& !stack->next)
		printf("bash: syntax error near unexpected token 'newline'\n");
	else if (token && token->type == CMD && tokens_list)
		printf("bash: syntax error near unexpected token '%s'\n",
			tokens_list->data);
	else
		printf("bash: syntax error near unexpected token '%s'\n", token->data);
}

t_token	*error_action(t_token *stack, t_token *tokens, t_token **output,
		int *state)
{
	parser_msg_error(stack, tokens, state);
	stack = ft_free_tokens(stack);
	if (output && *output)
		*output = ft_free_tokens(*output);
	if (tokens)
		tokens = ft_free_tokens(tokens);
	*state = -1;
	return (stack);
}
