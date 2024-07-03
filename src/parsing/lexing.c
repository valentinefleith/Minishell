/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:20:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 12:08:58 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type find_token_type(char *data, t_token **tokens)
{
	return WORD;
}

static t_token *create_node(char *buffer, int size, t_token **tokens)
{
	t_token *node;
	node = malloc(sizeof(t_token));
	if (!node)
		return NULL;
	node->data = malloc(size + 1);
	if (node->data == NULL)
	{
		free(node);
		return NULL;
	}
	ft_strlcpy(node->data, buffer, size + 1);
	node->type = find_token_type(node->data, tokens);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

static t_token *get_last_token(t_token *tokens)
{
	if (!tokens)
		return NULL;
	while (tokens->next)
		tokens = tokens->next;
	return tokens;
}

static void tokens_add_back(t_token **tokens, t_token *new)
{
	t_token *last;

	if (!tokens)
		return;
	if (!*tokens)
	{
		*tokens = new;
		return;
	}
	last = get_last_token(*tokens);
	last->next = new;
	new->prev = last;
}

static int get_size_next_token(char *buffer)
{
	int size;
	bool inside_quotes = false;
	
	size = 0;
	while (buffer[size])
	{
		if (buffer[size] == ' ' && !inside_quotes)
			return size + 1;
		if (buffer[size] == '\"')
		{
			if (!inside_quotes)
				inside_quotes = true;
			else
				inside_quotes = false;
		}
		size++;
	}
	return size;
}

t_token **tokenize_cmdline(char *buffer)
{
	t_token **tokens;
	t_token *new;
	int size;

	tokens = malloc(sizeof(t_token *));
	if (!tokens)
		return NULL;
	*tokens = NULL;
	while (*buffer)
	{
		size = get_size_next_token(buffer);
		new = create_node(buffer, size, tokens);
		if (!new)
		{
			//ft_free_tokens(tokens);
			return (NULL);
		}
		tokens_add_back(tokens, new);
		buffer += size;
	}
	return tokens;
}
