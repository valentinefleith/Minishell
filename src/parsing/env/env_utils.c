/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/21 17:53:44 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_last_node(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_env_list(t_env **list, t_env *new)
{
	t_env *last;
	
	if (!*list)
	{
		*list = new;
	}
	else
	{
		last = get_last_node(*list);
		last->next = new;
	}
}

t_env	*free_env_list(t_env **list)
{
	t_env	*save;

	while (*list)
	{
		save = (*list)->next;
		if (*list)
		{
			if ((*list)->name)
				free((*list)->name);
			if ((*list)->data)
				free((*list)->data);
			free(*list);
		}
		*list = save;
	}
	return (NULL);
}
