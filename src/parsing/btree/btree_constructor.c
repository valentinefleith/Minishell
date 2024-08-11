/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:41:51 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/09 13:36:20 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_create_node(char *data, int type)
{
	t_btree	*new;

	new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->item = ft_strdup(data);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_btree *btree_create_cmd(void)
{
	t_btree *new;
	
	new = malloc(sizeof(t_btree));
	if (!new)
		return NULL;
	new->item = ft_strdup("command");
	new->type = COMMAND;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
