/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/23 15:55:15 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*get_last_node(t_env_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_env_list(t_env_list **list, t_env_list *new)
{
	t_env_list	*last;

	if (!*list)
		*list = new;
	else
	{
		last = get_last_node(*list);
		last->next = new;
	}
}
