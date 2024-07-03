/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:37:09 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 21:54:54 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node(char *buffer, int size)
{
	t_token	*node;
	char *data;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	data = ft_substr(buffer, 0, size);
	if (!data)
		return NULL;
	node->data = ft_strtrim(data, " ");
	if (node->data == NULL)
	{
		free(node);
		return (NULL);
	}
	node->type = UNDEFINED;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

void	tokens_add_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!tokens)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = get_last_token(*tokens);
	last->next = new;
	new->prev = last;
}
