/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:50 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/15 15:06:29 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Builds the output token list from the stack.
 *
 * This function concatenates tokens of specific types from the stack and
 * adds them to the output token list. It also frees the stack after processing.
 */
void	build_output(t_token **stack, t_token **output)
{
	t_token	*new;
	t_token	*save;

	new = NULL;
	save = *stack;
	while (*stack)
	{
		new = copy_token(*stack, new);
		tokens_add_back(output, new);
		*stack = (*stack)->next;
	}
	*stack = save;
	while (*stack)
	{
		save = (*stack)->next;
		if (*stack)
			free(*stack);
		*stack = save;
	}
}

// void	parsing_tokens_arg(t_token *output, t_env *env)
// {
// 	char	*str;
// 	int		size_arg;
// 	int		nb_dollar;
// 	int		i;

// 	size_arg = 0;
// 	// if (arg[1][0] == DOUBLE_QUOTE || arg[1][0] == SINGLE_QUOTE)
// 	// 	size_arg += 1;
// 	// for each node of the output and and each cell of arg's tab
// 		// count nb dollar and if var exist then returns the nb of var to extend
// 			// if yes -> get the total size of new the new string
// 			// then copy the new arg
// 	i = 1;
// 	while (output)
// 	{
// 		while (output->arg[i])
// 		{
// 			nb_dollar = check_if_expansion_var(output->arg[i], env);
// 			if (nb_dollar > 0)
// 				str = parsing_env_var(output->arg[i], nb_dollar);
// 			else
// 				str = remove_quotation(output->arg[i]);
// 			if (output->arg[i])
// 				free(output->arg[i]);
// 			output->arg[i] = str;
// 			i++;
// 		}
// 		output = output->next;
// 	}
// }

// char	*parsing_env_var(char *arg, int nb_dollar)
// {
// 	char	*new_arg;
// 	t_env	*var;
// 	int		i;
// 	int		j;
	
// 	// incrementer new_size jusqu'a premier dollar
// 		// si dollar
// 		//  si search(..) n'est pas null
// 			// nb_dollar--
// 			// add the size of the value
// 	new_size = 0;
// 	i = 0;
// 	j = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i + 1] == '$')
// 		{
// 			var = search_var_in_env();
// 		}
// 		i++;
// 	}
// }

// /**
//  * If detects a dollar in arg string, check if the var exists in env list,
//  * returns the number of dollar detected and matched.
//  */
// int	check_if_expansion_var(char *arg, t_env *env)
// {
// 	int		i;
// 	int		nb;
// 	char	*dollar;
	
// 	nb = 0;
// 	i = 0;
// 	dollar = NULL;
// 	while (arg[i])
// 	{
// 		dollar = ft_strchr(arg + i, '$');
// 		if (dollar)
// 		{
// 			arg = dollar;
// 			if (search_var_in_env(env, get_var_name(arg)))
// 				nb++;
// 		}
// 		i++;
// 	}
// 	return (nb);
// }

// char	*get_var_name(char *arg)
// {
// 	char	*name;
// 	int		i;
// 	int		j;
	
// 	if (!arg)
// 		return (NULL);
// 	name = NULL;
// 	i = 1;
// 	j = 0;
// 	while (arg[i] && !ft_isblank(arg[i])
// 		&& arg[i] != SINGLE_QUOTE && arg[i] != DOUBLE_QUOTE)
// 	{
// 		name[j] = arg[i];
// 		i++;
// 		j++;
// 	}
// 	return (name);
// }

// t_env	*search_var_in_env(t_env *env_list, char *name)
// {
// 	while (env_list)
// 	{
// 		if (ft_strncmp(env_list->name, name, ft_strlen(env_list->name)))
// 			return (env_list);
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }


// void	checking_cmd_syntax(t_token *cmd, int *state)
// {
// 	int	i;
	
// 	if (cmd->type != CMD || !cmd->data)
// 		return ;
// 	i = 0;
// 	while (cmd->data[i])
// 	{
// 		if (!ft_isalpha(cmd->data[i]))
// 			*state = 42;
// 		i++;
// 	}
// }

t_token	*copy_token(t_token *stack, t_token *new)
{
	new = malloc(sizeof(t_token));
	if (!new)
	{
		printf("Error: while allocation\n");
		return (NULL);
	}
	new->type = stack->type;
	new->arg = stack->arg;
	new->data = stack->data;
	new->next = NULL;
	return (new);
}
