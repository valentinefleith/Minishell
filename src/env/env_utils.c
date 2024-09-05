/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/05 17:53:29 by luvallee         ###   ########.fr       */
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
	t_env_list *last;
	
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

t_env_list	*free_env_list(t_env_list **list)
{
	t_env_list	*save;

	if (!list || !*list)
		return (NULL);
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

void		print_env_list(t_env_list *env)
{
	while(env)
	{
		printf("%s=%s\n", env->name, env->data);
		env = env->next;
	}
}
