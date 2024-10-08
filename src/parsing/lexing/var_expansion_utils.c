/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:52:16 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/02 22:05:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_varname(char *data, int index)
{
	int	len;

	len = 0;
	while (data[index + len] && (ft_isalnum(data[index + len])
			|| ft_strchr("?_", data[index + len])))
	{
		if (len == 0 && ft_isdigit(data[index]))
			return (1);
		len++;
	}
	return (len);
}

t_env_list	*find_target_variable(t_env_list *env_list, char *data, int index)
{
	size_t	var_len;

	if (!data)
		return (NULL);
	if (data[index] == '?')
		var_len = 1;
	else
		var_len = get_len_varname(data, index);
	while (env_list)
	{
		if (!env_list || !env_list->name || var_len <= 0 || !data)
			return (NULL);
		if (ft_strlen(env_list->name) == var_len && !ft_strncmp(env_list->name,
				data + index, var_len))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	update_quote_status(bool *in_single_quotes, bool *in_double_quotes,
		char c)
{
	if (c == DOUBLE_QUOTE && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
	if (c == SINGLE_QUOTE && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
}

int	copy_beginning_data(int index, char *dest, char *src)
{
	int	i;

	i = 0;
	while (i < index)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}
