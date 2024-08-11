/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_destructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:29 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/22 16:47:18 by vafleith         ###   ########.fr       */
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
			free((*tokens)->data);
			free(*tokens);
		}
		*tokens = next;
	}
	/*if (tokens)
		free(tokens);*/
	return (NULL);
}


t_token *quote_error(t_token **tokens)
{
	ft_printf("unclosed quote.\n");
	return ft_free_tokens(tokens);
}
