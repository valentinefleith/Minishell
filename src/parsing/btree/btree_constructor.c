/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:41:51 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 20:03:18 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"

t_btree	*btree_create_node(char **data, int type)
{
	t_btree	*new;

	new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->item = ft_strsdup(data);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_btree *btree_create_cmd(void)
{
	t_btree *new;
	char **item;

	item = malloc(2 * sizeof(char *));
	if (!item)
		return NULL;
	item[0] = ft_strdup("command");
	item[1] = 0;
	if (!item)
		return NULL;
	new = malloc(sizeof(t_btree));
	if (!new)
	{
		ft_free_tab(item);
		return NULL;
	}
	new->item = item;
	new->type = COMMAND;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
