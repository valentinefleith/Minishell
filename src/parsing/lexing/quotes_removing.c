/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:35:59 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/31 19:53:04 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_size(char *data)
{
	int		size;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	size = 0;
	inside_single_quotes = false;
	inside_double_quotes = false;
	while (*data)
	{
		if (*data == SINGLE_QUOTE && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (*data == DOUBLE_QUOTE && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else
			size++;
		data++;
	}
	return (size);
}

static char	*fill_without_quotes(char *src, char *dest)
{
	bool	inside_single_quotes;
	bool	inside_double_quotes;
	int		i;

	i = 0;
	inside_single_quotes = false;
	inside_double_quotes = false;
	while (*src)
	{
		if (*src == SINGLE_QUOTE && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (*src == DOUBLE_QUOTE && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else
		{
			dest[i] = *src;
			i++;
		}
		src++;
	}
	dest[i] = *src;
	return (dest);
}

char	*remove_quotes(char *data)
{
	int		new_size;
	char	*new;

	if (!data)
		return (NULL);
	new_size = get_new_size(data);
	new = malloc((1 + new_size) * sizeof(char));
	if (!new)
		return (NULL);
	new = fill_without_quotes(data, new);
	free(data);
	return (new);
}
