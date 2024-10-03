/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/03 16:10:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_varname(char *data, int *index)
{
	int		new_len;
	char	*new;
	int		len_varname;
	int		i;

	len_varname = get_len_varname(data, *index + 1);
	new_len = ft_strlen(data) - (len_varname + 1);
	new = ft_calloc(new_len + 2, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (data[i] && i < (*index))
	{
		new[i] = data[i];
		i++;
	}
	new[i] = 2;
	i++;
	while (data[i + len_varname])
	{
		new[i] = data[i + len_varname];
		i++;
	}
	free(data);
	return (new);
}

static void	copy_right_data(char *dest, char *src, int index,
		t_env_list *target_var)
{
	int	i;
	int	j;
	int	k;
	int	new_len;

	new_len = ft_strlen(src) - (1 + ft_strlen(target_var->name))
		+ ft_strlen(target_var->data);
	i = copy_beginning_data(index, dest, src);
	j = 0;
	while (target_var->data[j])
	{
		dest[i] = target_var->data[j];
		j++;
		i++;
	}
	k = index + 1 + ft_strlen(target_var->name);
	while (i < new_len)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	dest[i] = '\0';
}

static char	*replace_variable(char *data, int *index, t_env *envs)
{
	int			new_len;
	char		*new;
	t_env_list	*target_var;

	target_var = find_target_variable(envs->env_list, data, *index);
	(*index)--;
	if (!target_var || !target_var->data)
		return (remove_varname(data, index));
	new_len = ft_strlen(data) - (1 + ft_strlen(target_var->name))
		+ ft_strlen(target_var->data);
	new = ft_calloc(1 + new_len, sizeof(char));
	if (!new)
	{
		free(data);
		return (NULL);
	}
	copy_right_data(new, data, *index, target_var);
	free(data);
	*index += ft_strlen(target_var->data);
	return (new);
}

static char	*expand_variables(char *data, t_env *envs)
{
	int		i;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	i = 0;
	inside_single_quotes = false;
	inside_double_quotes = false;
	while (data[i])
	{
		update_quote_status(&inside_single_quotes, &inside_double_quotes,
			data[i]);
		if (data[i] == '$' && !inside_single_quotes)
		{
			i++;
			if (ft_isalnum(data[i]) || ft_strchr("?_'\"", data[i]))
			{
				data = replace_variable(data, &i, envs);
				if (!data)
					return (NULL);
			}
		}
		else
			i++;
	}
	return (data);
}

t_token	*perform_var_expansion(t_token *tokens, t_env *envs)
{
	t_token	*start;

	start = tokens;
	if (g_signal != 0)
		update_exit_status(envs->env_list, 0);
	while (tokens)
	{
		tokens->data = expand_variables(tokens->data, envs);
		if (tokens->data == NULL)
		{
			start = ft_free_tokens(start);
			return (start);
		}
		tokens->data = remove_quotes(tokens->data);
		if (tokens->data == NULL)
		{
			start = ft_free_tokens(start);
			return (start);
		}
		tokens = tokens->next;
	}
	return (start);
}
