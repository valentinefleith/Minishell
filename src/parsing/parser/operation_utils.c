/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/02 12:28:45 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_input_arg(t_token *stack_token)
{
	t_token	*word_token;
	t_token	*last_token;
	int		pos;

	if (!stack_token)
		return (-1);
	word_token = find_last_type(stack_token, WORD);
	if (!word_token)
		return (1);
	pos = 1;
	while (stack_token->arg[pos])
		pos++;
	stack_token->arg[pos] = ft_strdup(word_token->data);
	if (!stack_token->arg[pos])
		return (ft_free_tab(stack_token->arg), -1);
	last_token = get_second_last_token(stack_token);
	ft_free_token_node(word_token);
	last_token->next = NULL;
	return (0);
}

t_token	*get_second_last_token(t_token *tokens)
{
	t_token	*second_last;

	second_last = NULL;
	while (tokens)
	{
		if (tokens->next == NULL)
			return (second_last);
		else
			second_last = tokens;
		tokens = tokens->next;
	}
	return (second_last);
}

t_token	*find_last_type(t_token *stack, int type)
{
	t_token	*last;

	if (!stack)
		return (NULL);
	last = NULL;
	while (stack)
	{
		if (stack->type == type)
			last = stack;
		stack = stack->next;
	}
	return (last);
}

int	count_nb_arg(t_token *stack)
{
	int	nb;

	nb = 0;
	while (stack && stack->type != PIPE)
	{
		if (stack->type == WORD)
			nb++;
		stack = stack->next;
	}
	return (nb);
}
