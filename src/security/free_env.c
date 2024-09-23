/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:54:00 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/23 15:55:21 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*free_envs(t_env *envs)
{
	if (envs->env_tab)
		ft_free_tab(envs->env_tab);
	if (envs->env_list)
		envs->env_list = free_env_list(envs->env_list);
	free(envs);
	envs = NULL;
	return (envs);
}

t_env_list	*free_env_list(t_env_list *list)
{
	t_env_list	*save;

	if (!list)
		return (NULL);
	while (list)
	{
		save = list->next;
		if (list)
		{
			if (list->name)
				free(list->name);
			if (list->data)
				free(list->data);
			free(list);
		}
		list = save;
	}
	return (NULL);
}