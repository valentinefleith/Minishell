/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:26:03 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/24 13:45:19 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*get_prev_node(t_env_list *env_list, char *target)
{
	size_t	len;

	if (!env_list || !target)
		return (NULL);
	len = ft_strlen(target);
	while (env_list && env_list->next)
	{
		if (len == ft_strlen(env_list->next->name) 
			&& !ft_strncmp(env_list->next->name, target, len))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	ft_unset(t_env *envs, char **arg)
{
	t_env_list	*var;
	t_env_list	*save_prev;
	t_env_list	*save_next;
	int		i;

	i = 1;
	while (arg[i])
	{
		save_prev = get_prev_node(envs->env_list, arg[i]);
		if (save_prev)
			var = save_prev->next;
		if (var && !ft_strncmp(var->name, arg[i], ft_strlen(arg[i])))
		{
			save_next = var->next;
			if (var->name)
				free(var->name);
			if (var->data)
				free(var->data);
			free(var);
			save_prev->next = save_next;
		}
		i++;
	}
	return (refresh_env_tab(envs));
}
