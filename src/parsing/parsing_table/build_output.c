/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:50 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/19 17:09:33 by luvallee         ###   ########.fr       */
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

void	parsing_tokens_arg(t_token *output, t_env *env)
{
	char	*new_str;
	int		nb_dollar;
	int		i;

	while (output)
	{
		i = 0;
		while (output->arg && output->arg[i])
		{
			nb_dollar = count_var_expansion(output->arg[i], env);
			if (nb_dollar > 0)
			{
				new_str = parsing_env_var(output->arg[i], env);
				if (output->arg[i])
					free(output->arg[i]);
				output->arg[i] = new_str;
			}
			i++;
		}
		output = output->next;
	}
}

char	*parsing_env_var(char *arg, t_env *env)
{
	char	*new_str;
	t_env	*var_data;
	int		i;
	int		j;
	int		k;
	
	new_str = malloc(sizeof(char *) * get_new_str_len(arg, env));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			var_data = search_var_in_env(env, get_var_name(&arg[i]));
			if (var_data)
			{
				k = 0;
				while (var_data->data[k])
				{
					new_str[j] = var_data->data[k];
					j++;
					k++;
				}
				while (arg[i] && (arg[i] != 32 || !(arg[i] >= 9 && arg[i] <= 13)))
					i++;
			}
		}
		else
		{
			new_str[j] = arg[i];
			j++;	
			i++;
		}
	}
	return (new_str);
}

int	get_new_str_len(char *arg, t_env *env)
{
	t_env	*var_data;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] != '$')
		{
			i++;
			len++;
		}
		else
		{
			var_data = search_var_in_env(env, get_var_name(&arg[i]));
			if (var_data)
			{
				j = 0;
				while (var_data->data[j])
				{
					len++;
					j++;
				}
				while (arg[i] && (arg[i] != 32 || !(arg[i] >= 9 && arg[i] <= 13)))
					i++;
			}
		}
	}
	return (len);
}

/**
 * If detects a dollar in arg string, check if the var exists in env list,
 * returns the number of dollar detected and matched.
 */
int	count_var_expansion(char *arg, t_env *env)
{
	int		i;
	int		nb;
	char	*dollar;
	
	nb = 0;
	i = 0;
	dollar = NULL;
	while (arg[i])
	{
		dollar = ft_strchr(arg + i, '$');
		if (dollar)
		{
			arg = dollar;
			if (search_var_in_env(env, get_var_name(arg)))
				nb++;
		}
		i++;
	}
	return (nb);
}

char	*get_var_name(char *arg)
{
	char	*name;
	int		i;
	
	if (!arg)
		return (NULL);
	name = NULL;
	i = 1;
	while (arg[i] && !ft_isblank(arg[i])
		&& arg[i] != SINGLE_QUOTE && arg[i] != DOUBLE_QUOTE)
		i++;
	name = ft_substr(arg, 1, i - 1);
	return (name);
}

t_env	*search_var_in_env(t_env *env_list, char *name)
{
	size_t	len;
	
	len = ft_strlen(name);
	while (env_list)
	{
		if (len == ft_strlen(env_list->name) && !ft_strncmp(env_list->name, name, len))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}


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
