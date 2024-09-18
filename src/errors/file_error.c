/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:18:26 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/18 16:31:56 by vafleith         ###   ########.fr       */
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

void check_file_error(t_token *tokens, t_env *envs)
{
	if (!tokens)
		return;
	if (is_only_slash_dot(tokens->data))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tokens->data, 2);
		ft_putstr_fd(": Is a directory.\n", 2);
		tokens = ft_free_tokens(tokens);
		return;
	}
	//if (ft_strchr(tokens->data, '/'))
	//{
	//	ft_putstr_fd("bash: ");
	//}
}
