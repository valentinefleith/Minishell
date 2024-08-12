/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_destructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:29 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 17:56:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_free_tokens(t_token **tokens)
{
	t_token *next;
	
	while (*tokens)
	{
		next = (*tokens)->next;
		if (*tokens)
		{
			if ((*tokens)->data)
				free((*tokens)->data);
			if ((*tokens)->arg)
				ft_free_tab((*tokens)->arg);
			free(*tokens);
		}
		*tokens = next;
	}
	// if (tokens)
	// 	free(tokens);
	return (NULL);
}

void	ft_free_token_node(t_token **token)
{
	if ((*token)->data)
		free((*token)->data);
	if ((*token)->arg)
		ft_free_tab((*token)->arg);
	if (*token)
		free(*token);
	*token = NULL;
}