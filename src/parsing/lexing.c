/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:20:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 16:11:40 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"

t_token_type	find_token_type(char *data, t_token **tokens)
{
	// data = ft_strstrip(data);
	return (WORD);
}

static int	get_size_next_token(char *buffer)
{
	int		size;
	bool	inside_quotes;

	inside_quotes = false;
	size = 0;
	while (buffer[size])
	{
		if (buffer[size] == ' ' && !inside_quotes)
			return (size + 1);
		if (buffer[size] == '\"')
		{
			if (!inside_quotes)
				inside_quotes = true;
			else
				inside_quotes = false;
		}
		size++;
	}
	return (size);
}

t_token	**tokenize_cmdline(char *buffer)
{
	t_token	**tokens;
	t_token	*new;
	int		size;

	tokens = malloc(sizeof(t_token *));
	if (!tokens)
		return (NULL);
	*tokens = NULL;
	while (*buffer)
	{
		size = get_size_next_token(buffer);
		if (*buffer == ' ' && size == 1)
		{
			buffer++;
			continue ;
		}
		new = create_node(buffer, size, tokens);
		if (!new)
			return (ft_free_tokens(tokens));
		tokens_add_back(tokens, new);
		buffer += size;
	}
	return (tokens);
}
