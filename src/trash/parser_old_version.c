/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/05 14:14:15 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"

void	debug_parser(t_token **stack, t_token **input, int state, int ope)
{
	static int i = 0;
	
	i += 1;
	(void)ope;
	printf("                                      \n");
	printf("                                      \n");
	printf("-------------- etape %d --------------\n", i);
	printf("                                      \n");
	printf("-------------- STATE %d --------------\n", state);
	printf("                                      \n");
	// printf("-------------- OPE ");
	// if (ope == shift)
	// 	printf("shift ");
	// if (ope == reduce)
	// 	printf("reduce ");
	// if (ope == accept)
	// 	printf("accept ");
	// printf("--------------\n");
	debug_print_input(input);
	debug_print_stack(stack);
}

t_btree  *parser(t_token **input_tokens, t_btree *tree)
{
	t_operation	rules[9];
	t_token		*stack;
	t_token		*input;
	int			action;
	int			state;

	if (!(*input_tokens))
		return (NULL);
	get_grammar_rules(rules);
	input = *input_tokens;
	stack = NULL;
	state = 1;
	action = shift;
	shift_operation(&stack, &input);
	while (action != accept)
	{
		action = parsing_table(&state, rules, &stack, input);
		if (action == shift)
			shift_operation(&stack, &input);
		else if (action == reduce)
			reduce_operation(&stack, &tree, &state);
		else if (action == error)
			error_operation(&stack, &input);
		// debug_parser(&stack, &input, state, action);
	}
	return (tree);
}

static int find_size_of_full_cmd(t_token *stack)
{
	int nb;
	
	nb = 1; // je pars du principe ici qu'il y a toujours au moins un token `command`, c'est bien ca?
	while (stack)
	{
		if (stack->type == cmd_suffix)
			nb++;
		stack = stack->next;
	}
	return nb;
}

static char **list_to_array(t_token *stack)
{
	t_token *cmd;
	char **full_cmd;
	int i;

	full_cmd = malloc(find_size_of_full_cmd(stack) * sizeof(char *) + 1);
	if (!full_cmd)
		return NULL;
	cmd = find_in_stack(&stack, command);
	while (cmd)
	{
		if (cmd->type == cmd_suffix)
		{
			full_cmd[i] = ft_strdup(cmd->data);
			if (!full_cmd[i])
			{
				ft_free_tab(full_cmd);
				return NULL;
			}
			i++;
		}
		cmd = cmd->next;
	}
	full_cmd[i] = 0;
	return full_cmd;
}

// si on a une commande dans la stack alors
//    on concatène la commande avec les cmd_suffix si il y en a
//    on cree un noeud "command" pour l'arbre
//    ce noeud "commande" pointe vers un autre noeud a sa droite si il existe cmd_prefix dans la stack
//    ce noeud "commande" pointe vers un autre noeud a sa gauche qui contient la commande (ex: type = cmd data = echo/"salut")
// le noeud "commande" est la tete actuelle de l'arbre pour l'instant
// puis on supprime les elements de la stack qui ont servi a la creation des noeuds de l'arbre
void	monitor_stack(t_token **stack, t_btree **tree)
{
	t_btree	*root;
	t_token *node;

	if (find_in_stack(stack, cmd_suffix) != NULL)
		concatenate_cmd_to_param(stack);
	root = btree_create_node("command", command);
	if (btree_is_empty(root))
		return;
	node = find_in_stack(stack, cmd_prefix);
	if (node)
		root->left = btree_create_node(node->data, cmd_prefix);
	node = find_in_stack(stack, command);
	root->right = btree_create_node(node->data, cmd);
	if (btree_is_empty(*tree))
		*tree = root;
	else
	{
		if (btree_is_empty((*tree)->left))
			(*tree)->left = root;
		else
			(*tree)->right = root;
	}
	// ft_free_tokens(stack);
}

static t_token *get_last_suffix(t_token *stack)
{
	t_token *node;
	node = stack;
	while (stack)
	{
		if (stack->type == cmd_suffix)
			node = stack;
		stack = stack->next;
	}
	return node;
}

// Je t'ecris ici en pseudo code a quoi pourrait ressembler la nouvelle fonction
// le probleme ici c'est que notre struct t_token prend un char * et pas un char **.
// Peut etre qu'il faudrait :
// 1) creer une nouvelle struct
// ou 2) ajouter un char ** dans notre struct existante, mais ca necessite quand meme
// de re faire des fonctions de construction en fonction de si on envoie un char *
// ou un bien un char **. Je t'avoue que je sais pas trop ce qui est le mieux
// et ca depend aussi de la facon dont tu construis ta stack etc. donc a voir selon
// ce que tu penses etre le mieux!

void concatenate_cmd_to_param(t_token **stack)
{
	t_token *new;
	t_token *last_suffix;
	char **concatenated;

	concatenated = list_to_array(*stack);
	if (!concatenated)
		return;
	new = create_node(concatenated); // la fonction create node est a refaire du coup enfin
	// il faut pouvoir accepter les char ** en argument.
	last_suffix = get_last_suffix(*stack);
	new->next = last_suffix->next; //on connecte le nouveau noeud a la suite de la liste
	last_suffix->next = NULL; // on ferme le debut de l'ancienne liste par un NULL
	// ici trouver un moyen de free depuis le debut de la command jusqu'au last suffix
	// sans perdre le pointeur vers *stack.
	*stack = new;
}

/*
void	concatenate_cmd_to_param(t_token **stack)
{
	// t_token	*cmd_suffix;
	t_token	*node;
	t_token	*cmd;

	if (!*stack)
		return ;
	cmd = find_in_stack(stack, command);
	node = cmd;
	while (node)
	{
		if (node->type == cmd_suffix)
			ft_strlcat(cmd->data, node->data, ft_strlen(cmd->data) + 1);
		node = node->next;
	}
}*/
