/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:20:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/22 16:50:52 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
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

bool	check_quote_status(bool inside_quotes, bool inside_opposite_quotes)
{
	if (!inside_quotes)
		return (true);
	return (inside_opposite_quotes);
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

static void quote_errors_exit(char *buffer, t_token **tokens)
{
	ft_printf("unclosed quotes. processus exited.\n");
	free(buffer);
	ft_free_tokens(tokens);
	exit(1);
}

t_token	*tokenize_cmdline(char *buffer)
{
	t_token	*tokens;
	t_token	*new;
	int		size;

	tokens = NULL;
	while (*buffer)
	{
		size = get_size_next_token(buffer);
		if (size < 0)
			quote_errors_exit(buffer, &tokens);
		if (*buffer == ' ' && size == 1)
		{
			buffer++;
			continue ;
		}
		new = create_node(buffer, size);
		if (!new)
			return (ft_free_tokens(&tokens));
		tokens_add_back(&tokens, new);
		buffer += size;
	}
	fill_token_types(tokens);
	return (tokens);
}
