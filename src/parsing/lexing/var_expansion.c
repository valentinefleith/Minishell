/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/28 16:46:44 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *replace_variable(char *data, int index, t_env_list *target_var)
{
	int new_len;
	char *new;

	if (target_var)
		new_len = ft_strlen(data) - (1 + ft_strlen(target_var->name)) + ft_strlen(target_var->data);
	else
		new_len = ft_strlen(data) - 1;
	new = malloc((1 + new_len) * sizeof(char));
	if (!new)
		return NULL;
	int i = 0;
	while (i < index)
	{
		new[i] = data[i];
		i++;
	}
	int j = 0;
	while (target_var->data[j])
	{
		new[i] = target_var->data[j];
		j++;
		i++;
	}
	while (data[i - j])
	{
		new[i] = target_var->data[i - j];
		i++;
	}
	new[i] = '\0';
	free(data);
	return new;
}

static t_env_list *find_target_variable(t_env_list *env_list, char *data)
{
	while (env_list->next)
	{
		if (!ft_strncmp(env_list->name, data, ft_strlen(env_list->name)))
			return env_list;
		env_list = env_list->next;
	}
	return NULL;
}

static char *expand_variables(char *data, t_env *envs)
{
	int i = 0;
	t_env_list *target_var;

	bool inside_double_quotes = false;
	while (data[i])
	{
		if (data[i] == DOUBLE_QUOTE)
			inside_double_quotes = !inside_double_quotes;
		if (data[i] == '$' && !inside_double_quotes)
		{
			i++;
			if (ft_isalpha(data[i]))
			{
				target_var = find_target_variable(envs->env_list, data + i);
				data = replace_variable(data, i - 1, target_var);
				if (!data)
					return NULL;
				i = 0;
			}
		}
		else
			i++;
	}
	return data;
}

void perform_var_expansion(t_token *tokens, t_env *envs)
{
	t_token *start;

	start = tokens;
	while (tokens)
	{
		tokens->data = expand_variables(tokens->data, envs);
		if (tokens->data == NULL)
		{
			ft_free_tokens(&start);
			return;
			// exit?
		}
		tokens = tokens->next;
	}
}
