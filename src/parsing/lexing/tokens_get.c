/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:37:09 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/09 13:35:33 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token	*get_first_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->prev)
		tokens = tokens->prev;
	return (tokens);
}

t_token *get_last_pipe(t_token *tokens)
{
	if (!tokens)
		return NULL;
	while (tokens && tokens->type != PIPE)
		tokens = tokens->prev;
	return (tokens);
}
