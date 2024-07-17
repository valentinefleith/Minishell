/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_destructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:19:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/17 16:11:36 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	btree_free(t_btree *tree)
{
	if (btree_is_empty(tree))
		return ;
	btree_free(tree->left);
	btree_free(tree->right);
	free(tree->item);
	free(tree);
}
