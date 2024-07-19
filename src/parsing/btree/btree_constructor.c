/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:41:51 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/17 16:11:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_create_node(t_token *item)
{
	t_btree	*new;

	new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->item = ft_strdup(item->data);
	new->type = item->type;
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
