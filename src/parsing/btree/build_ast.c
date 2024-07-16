/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:40:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/16 18:24:17 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*create_ast(t_token *tokens)
{
	t_btree	*tree;
	t_token	*start;

	start = tokens;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tree = btree_create_node(tokens);
			if (!tree)
				return (NULL);
			// tree->left = parse_cmd(start);
			tree->left = btree_create_node(tokens->prev);
			if (!tree->left)
			{
				btree_free(tree);
				return (NULL);
			}
			tree->right = create_ast(tokens->next);
		}
		tokens = tokens->next;
	}
	return (tree);
}

// t_btree	*btree_insert_node(t_btree **tree, t_btree *node)
//{
//	if (!tree)
//		return (NULL);
//	if (!*tree)
//		return (*tree = node);
//}

/*t_btree	**create_ast(t_token *tokens)
{
	t_btree	**tree;
	t_btree	*node;

	tree = malloc(sizeof(t_btree *));
	if (!tree)
		return (NULL);
	while (tokens)
	{
		node = btree_create_node(tokens);
		if (!node)
		{
			btree_free(*tree);
			free(tree);
			return (NULL);
		}
		*tree = btree_insert_node(tree, node);
		tokens = tokens->next;
	}
	return (tree);
}*/
