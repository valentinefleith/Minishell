/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:24:49 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/16 18:49:24 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/* write or find a recursive function who does this*/
void btree_print(t_btree *tree)
{
	t_btree *right;
	t_btree *left;
	ft_printf("Etage 1 : \n");
	print_single_token_type(tree->type);
	ft_printf("\n");
	ft_printf("Etage 2 :\n");
	print_single_token_type(tree->left->type);
	print_single_token_type(tree->right->type);

}
