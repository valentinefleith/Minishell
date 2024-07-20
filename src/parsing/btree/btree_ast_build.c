/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_ast_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:40:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/20 17:06:09 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_token *find_next_pipe(t_token *tokens)
// {
// 	while (tokens && tokens->type != PIPE)
// 		tokens = tokens->next;
// 	return tokens;
// }

// static t_btree *create_command_node(t_token *tokens, t_token *next_pipe)
// {
// 	t_btree *command;
	
// 	command = btree_create_cmd();
// 	if (!command)
// 		return NULL;
// 	// command->left = btree_create_node(tokens);
// 	// pour l'instant ca marche que si on a 1 seul truc dans la commande
// 	command->right = NULL;

// 	//while (tokens != next_pipe)
// 	//{
// 	//	
// 	//	tokens = tokens->next;
// 	//}
// 	return command;
// }

// t_btree *create_ast(t_token *tokens)
// {
// 	t_btree *root;
// 	t_token *next_pipe;

// 	if (!tokens)
// 		return NULL;
// 	next_pipe = find_next_pipe(tokens);
// 	if (!next_pipe)
// 		return create_command_node(tokens, next_pipe);
// 	// root = btree_create_node(next_pipe);
// 	if (btree_is_empty(root))
// 		return NULL;
// 	root->left = create_command_node(tokens, next_pipe);
// 	if (btree_is_empty(root->left))
// 	{
// 		btree_free(root);
// 		return NULL;
// 	}
// 	root->right = create_ast(next_pipe->next);
// 	return root;
// }

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
