/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:20:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/19 12:39:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_token_types(t_token *tokens)
{
	while (tokens)
	{
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
		else if (!ft_strncmp(tokens->data, "$", 1))
			tokens->type = ASSIGNMENT;
		else
			tokens->type = WORD;
		tokens = tokens->next;
	}
}

static int	handle_separator(char *buffer, int size)
{
	if (buffer[size] == ' ')
		return (size + 1);
	if (buffer[size] == '|' && !size)
		return (size + 1);
	if (buffer[size] == '>' || buffer[size] == '<')
	{
		if (!size && buffer[size + 1] == buffer[size])
			return (size + 2);
		if (!size)
			return (size + 1);
	}
	return (size);
}

static bool	check_quote_status(bool inside_quotes, bool inside_opposite_quotes)
{
	if (!inside_quotes)
		return (true);
	return (inside_opposite_quotes);
}

static int	get_size_next_token(char *buffer)
{
	int		size;
	bool	inside_double_quotes;
	bool	inside_simple_quotes;
	bool	inside_quotes;

	inside_double_quotes = false;
	inside_simple_quotes = false;
	size = 0;
	while (buffer[size])
	{
		inside_quotes = (inside_double_quotes || inside_simple_quotes);
		if (ft_strchr(" >|<", buffer[size]) && !inside_quotes)
			return (handle_separator(buffer, size));
		if (buffer[size] == DOUBLE_QUOTE)
			inside_double_quotes = check_quote_status(inside_quotes,
					inside_simple_quotes);
		if (buffer[size] == SINGLE_QUOTE)
			inside_simple_quotes = check_quote_status(inside_quotes,
					inside_double_quotes);
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
