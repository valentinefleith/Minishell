/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:24:49 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/17 17:17:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	padding(char ch, int n)
{
	int	i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void	print_structure(t_btree *root, int level)
{
	if (root == NULL)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		print_structure(root->right, level + 1);
		padding('\t', level);
		// printf ( "%d\n", root->type );
		print_single_token_type(root->type);
		printf(" <\n");
		print_structure(root->left, level + 1);
	}
}
