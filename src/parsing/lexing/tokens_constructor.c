/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:31:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/08 15:08:01 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node(char *buffer, int size)
{
	t_token	*node;
	char 	*data;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	data = ft_substr(buffer, 0, size);
	if (!data)
		return NULL;
	// node->data = ft_split(data, ' ');
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
