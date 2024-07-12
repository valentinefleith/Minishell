/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:19:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/12 17:25:24 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_create_node(t_token *item)
{
	t_btree	*new;

	new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->item = item->data;
	new->type = item->type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

bool isEmpty(t_btree *tree)
{
	return tree == NULL;
}

bool isLeaf(t_btree *tree)
{
	if (isEmpty(tree))
		return false;
	return (isEmpty(tree->left) && isEmpty(tree->right));
}
