/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:52:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/06 16:35:43 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	reduce_operation(t_token **stack, t_btree **tree, int *state)
// {
// 	if (!stack)
// 		*state = 0;
// 	if (*state == 1)
// 		replace_type(stack, WORD, cmd_name);
// 	if (*state == 3)
// 	{
// 		monitor_stack(stack, tree);
// 		replace_type(stack, command, program);
// 	}
// 	if (*state == 4 || *state == 7)
// 		replace_type(stack, cmd_name, command);
// 	if (*state == 8)
// 		replace_type(stack, cmd_suffix, cmd_suffix);
// 	if (*state == 6)
// 		replace_type(stack, WORD, cmd_suffix);
// 	*state = 0;
// }

void	reduce_action(t_token **stack, t_token **output, int *state)
{
	if (!stack)
		*state = 0;
	if (*state == 1)
		replace_type(stack, WORD, cmd_name);
	if (*state == 6)
		replace_type(stack, redirection, cmd_prefix);
	if (*state == 7) // concatenate (exemple) INPUT + WORD in stack to redirection
		reduce_type_redirection(stack);
	if (*state == 9)
		replace_type(stack, WORD, cmd_suffix);
	// if (*state == 11)
	// 	replace_type(stack, redirection, cmd_suffix);
	if (*state == 13) // concatenate cmd_suffix + WORD;
		cat_tokens_type(stack, cmd_suffix, WORD);
	if (*state == 10 || *state == 14) // build_output; and clear stack !!
	{
		build_output(stack, output);
		*state = 3;
		return ;
	}
	if (*state == 7)
		*state = 6;
	*state = 0;
}

void	reduce_type_redirection(t_token **stack)
{
	t_token	*new_node;
	int		type_redir;

	// on cherche le noeud dont on va remplacer le type et concatenate les arg;
	// dans notre header on a indique des enumerations -> input(=1),heredoc(=2),output(=3),append(=4)
	// grace a l'enum on va boucler pour parcourir tous les types de redirections et lorsqu'on trouve 
	// une correspondance dans la stack, on sauvegarde et on sort de la boucle
	type_redir = INPUT;
	while (type_redir != APPEND)
	{
		new_node = find_in_stack(stack, type_redir);
		if (new_node) //  && new_node->next->type == WORD ?? ajouter cette protection ??
			break;
		type_redir++;
	}
	new_node->data = cat_tokens_arg(stack, new_node->type, WORD);
	new_node->type = redirection;
	if (new_node->next)
	{
		free(new_node->next);
		new_node->next = NULL;
	}
}

void	cat_tokens_type(t_token **stack, int target, int old_type)
{
	t_token *new_node;

	new_node = find_in_stack(stack, target);
	if (!new_node)
		return ;
	new_node->test = cat_tokens_arg(stack, target, old_type);
	if (new_node->next)
	{
		free(new_node->next);
		new_node->next = NULL;
	}
}

void	shift_action(t_token **stack, t_token **input)
{
	t_token	*new_node;
	t_token	*tmp;

	if (!*input)
		return ;
	new_node = NULL;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		printf("Error: while allocation during shift action\n");
		return ;
	}
	new_node->data = (*input)->data;
	new_node->type = (*input)->type;
	new_node->next = NULL;
	tokens_add_back(stack, new_node);
	tmp = (*input)->next;
	free(*input);
	*input = tmp;
}

void	error_action(t_token **stack, t_token **input)
{
	printf("Error: with the input, do not fit with the parsing table\n");
	debug_print_stack(*stack, "STACK");
	debug_print_input(input);
	ft_free_tokens(input);
	ft_free_tokens(stack);
	exit(EXIT_FAILURE);
}