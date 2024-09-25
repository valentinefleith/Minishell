/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:11 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/25 14:54:12 by luvallee         ###   ########.fr       */
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

// static t_env_list	*create_node_env_list(t_env_list *env_list, char *name,
// 		char *data)
// {
// 	t_env_list	*new;

// 	if (!name || !data)
// 		return (NULL);
// 	new = malloc(sizeof(t_env_list));
// 	if (!new)
// 		return (printf("create_node_env: allocation error\n"), NULL);
// 	new->name = ft_strdup(name);
// 	if (!new->name)
// 	{
// 		free(new);
// 		return (printf("create_node_env: allocation error\n"), NULL);
// 	}
// 	new->data = ft_strdup(data);
// 	if (!new->data)
// 	{
// 		free(new);
// 		free(new->name);
// 		return (printf("create_node_env: allocation error\n"), NULL);
// 	}
// 	add_env_list(&env_list, new);
// 	return (env_list);
// }

// t_env_list	*no_env_var(void)
// {
// 	t_env_list	*env_list;
// 	char		buffer[1024];

// 	env_list = malloc(sizeof(t_env_list));
// 	if (!env_list)
// 		return (printf("no_env_var.0: allocation error\n"), NULL);
// 	env_list->name = ft_strdup("PWD");
// 	env_list->data = ft_strdup(getcwd(buffer, 1024));
// 	if (!env_list->name || !env_list->data)
// 		return (free_env_list(env_list));
// 	if (!create_node_env_list(env_list, "SHLVL", getenv("SHLVL")))
// 		return (printf("no_env_var.1: allocation error\n"), free_env_list(env_list));
// 	if (!create_node_env_list(env_list, "_", getenv("_")))
// 		return (printf("no_env_var.2: allocation error\n"), free_env_list(env_list));
// 	return (env_list);
// }
