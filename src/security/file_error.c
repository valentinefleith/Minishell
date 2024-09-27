/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:18:26 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/22 17:56:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_only_slash_dot(char *data)
{
	while (*data)
	{
		if (*data != '/' && *data != '.')
			return false;
		data++;
	}
	return true;
}

static bool is_only_dot(char *data)
{
	while (*data)
	{
		if (*data != '.')
			return false;
		data++;
	}
	return true;
}

t_token *check_file_error(t_token *tokens, t_env *envs)
{
	if (!tokens || !tokens->data)
		return tokens;
	if (ft_strlen(tokens->data) == 1 && tokens->data[0] == '.')
	{
		ft_putendl_fd("bash: .: filename argument required", 2);
		ft_free_tokens(tokens);
		tokens = NULL;
		update_exit_status(envs->env_list, 2);
		return tokens;
	}
	if (is_only_dot(tokens->data))
		return tokens;
	if (is_only_slash_dot(tokens->data))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tokens->data, 2);
		ft_putstr_fd(": Is a directory.\n", 2);
		ft_free_tokens(tokens);
		tokens = NULL;
		update_exit_status(envs->env_list, 126);
		return tokens;
	}
	return tokens;
}
