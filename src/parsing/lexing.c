/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:20:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/04 16:11:08 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_token_types(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type != UNDEFINED)
		{
			tokens = tokens->next;
			continue ;
		}
		if (!ft_strncmp(tokens->data, "<<", 2))
			tokens->type = HEREDOC;
		else if (!ft_strncmp(tokens->data, ">>", 2))
			tokens->type = APPEND;
		else if (!ft_strncmp(tokens->data, "<", 1))
			tokens->type = INPUT;
		else if (!ft_strncmp(tokens->data, ">", 1))
			tokens->type = OUTPUT;
		else if (!ft_strncmp(tokens->data, "|", 1))
			tokens->type = PIPE;
		else
			tokens->type = WORD;
		if ((tokens->type == INPUT || tokens->type == OUTPUT
				|| tokens->type == APPEND) && tokens->next)
			tokens->next->type = FILENAME;
		tokens = tokens->next;
	}
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
		if (buffer[size] == DOUBLE_QUOTE)
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
		new = create_node(buffer, size);
		if (!new)
			return (ft_free_tokens(tokens));
		tokens_add_back(tokens, new);
		buffer += size;
	}
	fill_token_types(*tokens);
	return (tokens);
}
