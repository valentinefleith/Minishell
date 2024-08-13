/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:42:21 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/16 17:45:48 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	btree_is_empty(t_btree *tree)
{
	return (tree == NULL);
}

bool	btree_is_leaf(t_btree *tree)
{
	if (btree_is_empty(tree))
		return (false);
	return (btree_is_empty(tree->left) && btree_is_empty(tree->right));
}
