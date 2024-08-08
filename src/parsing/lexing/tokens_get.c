/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:37:09 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/08 17:13:41 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token	*get_first_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->prev)
		tokens = tokens->prev;
	return (tokens);
}

t_token *get_last_pipe(t_token *tokens)
{
	if (!tokens)
		return NULL;
	while (tokens && tokens->type != PIPE)
		tokens = tokens->prev;
	return (tokens);
}

static int	get_size_next_token(char *buffer)
{
	int		size;
	bool	inside_double_quotes;
	bool	inside_single_quotes;
	bool	inside_quotes;

	inside_double_quotes = false;
	inside_single_quotes = false;
	inside_quotes = false;
	size = 0;
	while (buffer[size])
	{
		if (ft_strchr(" >|<", buffer[size]) && !inside_quotes)
			return (handle_separator(buffer, size));
		if (buffer[size] == DOUBLE_QUOTE && !inside_single_quotes)
			inside_double_quotes = check_quote_status(inside_quotes,
					inside_single_quotes);
		if (buffer[size] == SINGLE_QUOTE && !inside_double_quotes)
			inside_single_quotes = check_quote_status(inside_quotes,
					inside_double_quotes);
		size++;
		inside_quotes = (inside_double_quotes || inside_single_quotes);
	}
	if (inside_quotes)
		return (-1);
	return (size);
}
