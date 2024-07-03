/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:47:13 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 16:11:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

t_token **ft_free_tokens(t_token **tokens)
{
	t_token *next;

	while (*tokens)
	{
		next = (*tokens)->next;
		free(*tokens);
		*tokens = next;
	}
	free(tokens);
	return NULL;
}
