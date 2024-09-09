/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:24:49 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/21 15:51:36 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


static void	padding(char ch, int n)
{
	int	i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

static void ft_print_node_type(t_btree *node)
{
	if (node->type == COMMAND)
		printf(" cmd");
	if (node->type == PIPE)
		printf(" pipe");
	if (node->type == CMD)
		printf(" cmd");
	if (node->type == REDIR)
		printf(" redir");
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
		ft_print_node_type(root);
		// printf ( "%d\n", root->type );
		//print_single_token_type(root->type);
		printf(" <\n");
		print_structure(root->left, level + 1);
	}
}

void btree_print_details(t_btree *root, int level)
{
	if (btree_is_empty(root))
		return;
	printf("%ieme node:\n", level);
	printf("type: ");
	ft_print_node_type(root);
	printf(" /// content: ");
	if (root->item) {
		for (int i = 0; root->item[i]; i++)
		{
			printf("%s|", root->item[i]);
		}
		printf("\n");
	}
	else {
		printf("NULL\n");
	}
	btree_print_details(root->left, level + 1);
	btree_print_details(root->right, level + 2);
}
