/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_ast_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:40:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 19:51:37 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *find_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	return tokens;
}

static t_btree *create_command_tree(t_token *tokens, t_token *next_pipe)
{
	t_btree *command;
     
	command = btree_create_cmd();
	if (!command)
		return NULL;
	command->left = btree_create_node(tokens->arg, tokens->type);
	// pour l'instant ca marche que si on a 1 seul truc dans la commande
	command->right = NULL;

	//while (tokens != next_pipe)
	//{
	//	
	//	tokens = tokens->next;
	//}
	return command;
}

t_btree *create_ast(t_token *tokens)
{
	t_btree *root;
	t_token *next_pipe;

	if (!tokens)
		return NULL;
	next_pipe = find_next_pipe(tokens);
	if (!next_pipe)
		return create_command_tree(tokens, next_pipe);
	root = btree_create_node(NULL, PIPE);
	if (btree_is_empty(root))
		return NULL;
	root->left = create_command_tree(tokens, next_pipe);
	if (btree_is_empty(root->left))
	{
		btree_free(root);
		return NULL;
	}
	root->right = create_ast(next_pipe->next);
	return root;
}
