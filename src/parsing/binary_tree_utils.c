/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:19:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/14 22:55:16 by vafleith         ###   ########.fr       */
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

bool	is_empty(t_btree *tree)
{
	return (tree == NULL);
}

bool	is_leaf(t_btree *tree)
{
	if (is_empty(tree))
		return (false);
	return (is_empty(tree->left) && is_empty(tree->right));
}

void	btree_free(t_btree *tree)
{
	if (is_empty(tree))
		return ;
	btree_free(tree->left);
	btree_free(tree->right);
	free(tree);
}
