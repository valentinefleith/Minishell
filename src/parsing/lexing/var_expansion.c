/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/11 19:53:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_varname(char *data, int index)
{
	int		new_len;
	char	*new;
	int		len_varname;
	int		i;

	len_varname = get_len_varname(data, index);
	new_len = ft_strlen(data) - (len_varname + 1);
	new = malloc((new_len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (data[i] && i < index)
	{
		new[i] = data[i];
		i++;
	}
	while (data[i + len_varname])
	{
		new[i] = data[i + len_varname];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void	copy_right_data(char *dest, char *src, int index,
		t_env_list *target_var, int new_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < index)
	{
		dest[i] = src[i];
		i++;
	}
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

static char	*replace_variable(char *data, int index, t_env_list *target_var)
{
	int		new_len;
	char	*new;

	if (!target_var || !target_var->data)
		return (remove_varname(data, index));
	if (target_var)
		new_len = ft_strlen(data) - (1 + ft_strlen(target_var->name))
			+ ft_strlen(target_var->data);
	new = malloc((1 + new_len) * sizeof(char));
	if (!new)
		return (NULL);
	copy_right_data(new, data, index, target_var, new_len);
	free(data);
	return (new);
}

static char	*expand_variables(char *data, t_env *envs)
{
	int			i;
	t_env_list	*target_var;
	bool		inside_single_quotes;

	i = 0;
	inside_single_quotes = false;
	while (data[i])
	{
		if (data[i] == SINGLE_QUOTE)
			inside_single_quotes = !inside_single_quotes;
		if (data[i] == '$' && !inside_single_quotes)
		{
			i++;
			if (ft_isalnum(data[i]) || data[i] == '?' || data[i] == '_')
			{
				target_var = find_target_variable(envs->env_list, data, i);
				data = replace_variable(data, i - 1, target_var);
				if (!data)
					return (NULL);
				i = 0;
			}
		}
		else
			i++;
	}
	return (data);
}

void	perform_var_expansion(t_token *tokens, t_env *envs)
{
	t_token	*start;

	start = tokens;
	while (tokens)
	{
		tokens->data = expand_variables(tokens->data, envs);
		tokens->data = remove_quotes(tokens->data);
		if (tokens->data == NULL)
		{
			ft_free_tokens(&start);
			return ;
		}
		tokens = tokens->next;
	}
}
