/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/08 15:09:28 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
*	This function performs a "shift" action in a parser.
*   It moves the first token from the tokens list to the stack.
*   The new node's data and type are copied from the first token in the tokens list.
*   The new node is then added to the end of the stack.
*   The first token in the tokens list is removed and freed.
*/
void	shift_action(t_token **stack, t_token **tokens)
{
	t_token	*new_node;
	t_token	*tmp;

	if (!*tokens)
		return ;
	new_node = NULL;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		printf("Error: while allocation during shift action\n");
		return ;
	}
	new_node->data = ft_strdup((*tokens)->data);
	new_node->type = (*tokens)->type;
	new_node->next = NULL;
	tokens_add_back(stack, new_node);
	tmp = (*tokens)->next;
	free(*tokens);
	*tokens = tmp;
}

/**
 * Reduces the stack based on the current state and modifies the output.
 *
 * This function performs different actions based on the value of the state:
 * - If the state is 1, it replaces the type WORD with cmd_name.
 * - If the state is 6, it replaces the type redirection with cmd_prefix.
 * - If the state is 7, it concatenates INPUT and WORD in the stack to form a redirection.
 * - If the state is 9, it replaces the type WORD with cmd_suffix.
 * - If the state is 13, it concatenates cmd_suffix and WORD in the stack.
 * - If the state is 10 or 14, it builds the output from the stack and clears the stack, then sets the state to 8.
 * - If the state was 7, it sets the state to 6.
 * - Otherwise, it sets the state to 0.
 */
void	reduce_action(t_token **stack, t_token **output, int *state)
{
	if (!stack)
		*state = 0;
	if (*state == 1)
		replace_type(stack, WORD, cmd_name);
	if (*state == 6)
		replace_type(stack, redirection, cmd_prefix);
	if (*state == 7)
		reduce_type_redirection(stack);
	if (*state == 9)
		replace_type(stack, WORD, cmd_suffix);
	/* Je retire l'etape 11 parce que ca pose probleme de melanger les redirections avec 
		les cmd_suffix, quand on veut concatener une commande(cmd_name) et ses arguments(cmd_suffix) on veut pas
		avoir les redirections melangees la dedans
	if (*state == 11)
		replace_type(stack, redirection, cmd_suffix); */
	if (*state == 13)
		cat_tokens_type(stack, cmd_suffix, WORD);
	if (*state == 10 || *state == 14)
	{
		build_output(stack, output);
		*state = 8;
		return ;
	}
	if (*state == 7)
		*state = 6;
	*state = 0;
}

/**
 * This function reduces the stack by concatenating the token's type and WORD tokens to form a redirection.
 * It searches for the node in the stack that needs to have its type replaced and its arguments concatenated.
 * The node's data is then updated by concatenating its arguments.
 * The node's type is set to "redirection".
 * If the node has a next pointer, it is freed and set to NULL.
 */
void reduce_type_redirection(t_token **stack)
{
	t_token *new_node;
	int type_redir;

	type_redir = INPUT;
	// on cherche le noeud dont on va remplacer le type et concatenate les arg;
	// dans notre header on a indique des enumerations -> input(=1),heredoc(=2),output(=3),append(=4)
	// grace a l'enum on va boucler pour parcourir tous les types de redirections et lorsqu'on trouve 
	// une correspondance dans la stack, on sauvegarde et on sort de la boucle
	while (type_redir != APPEND)
	{
		new_node = find_in_stack(stack, type_redir);
		if (new_node)
			break;
		type_redir++;
	}
	new_node->arg = cat_tokens_arg(new_node, WORD);
	new_node->type = redirection;
	if (new_node->next)
	{
		free(new_node->next);
		new_node->next = NULL;
	}
}

/**
 * Concatenates tokens of a specific type from a stack.
 * @stack: The stack of tokens.
 * @target: The target token type to find in the stack.
 * @old_type: The type of the token to concatenate.
 *
 * This function searches for a token of the specified target type in the stack.
 * If found, it concatenates the token's data with additional data of the specified old_type.
 * It frees the next node and sets it to NULL.
 */
void	cat_tokens_type(t_token **stack, int target, int old_type)
{
	t_token *new_node;

	new_node = find_in_stack(stack, target);
	if (!new_node)
		return ;
	new_node->arg = cat_tokens_arg(new_node, old_type);
	if (new_node->next)
	{
		free(new_node->next);
		new_node->next = NULL;
	}
}

/**
 * Concatenates arguments for a given token.
 * @add: The type of token we want the data to concatenate.
 *
 * This function allocates memory for concatenating the token's data with additional data.
 * It returns a pointer to the concatenated data.
 */
char	**cat_tokens_arg(t_token *node, int add)
{
	char	**concatenation;
	int 	i;

	concatenation = malloc(get_cat_size(node, add) * sizeof(char *) + 2);
	if (!concatenation)
		return (NULL);
	concatenation[0] = ft_strdup(node->data);
	i = 1;
	while (node)
	{
		if (node->type == add)
		{
			concatenation[i] = ft_strdup(node->data);
			if (!concatenation[i])
			{
				ft_free_tab(concatenation);
				return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	concatenation[i] = 0;
	return (concatenation);
}
