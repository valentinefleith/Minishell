/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:46:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/06 16:14:32 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_envs(char **env)
{
	t_env_list	*env_list;
	char		**env_tab;
	t_env		*envs;
	
	envs = malloc(sizeof(t_env));
	if (!envs)
		return NULL;
	env_tab = ft_strsdup(env);
	if (!env_tab)
		return (NULL);
	env_list = NULL;
	env_list = build_env_list(env_list, env);
	// add_exit_status_var(env_list);
	envs->env_list = env_list;
	envs->env_tab = env_tab;
	return (envs);
}

t_env_list	*build_env_list(t_env_list *env, char **src_env)
{
	int			i;
	int			limit;
	t_env_list	*new;
	
	if (!src_env)
		return (NULL);
	i = 0;
	while (src_env[i])
	{
		limit = ft_get_index(src_env[i], '=');
		new = malloc(sizeof(t_env_list));
		if (!new)
			return (NULL);
		new->name = ft_substr(src_env[i], 0, limit);
		new->data = ft_substr(src_env[i], limit + 1, ft_strlen(src_env[i]));
		if (!new->name || !new->data)
		{
			free_env_list(&env);
			return (NULL);
		}
		new->next = NULL;
		add_env_list(&env, new);
		i++;
	}
	return (env);
}

void	update_exit_status(t_env_list *env_list, int exit_status)
{
	t_env_list	*var_status;

	var_status = ft_getenv(env_list, "?");
	if (!var_status)
		return ;
	if (var_status->data)
		free(var_status->data);
	var_status->data = ft_itoa(exit_status);
	// refresh_env_tab(envs);
}

void	add_exit_status_var(t_env_list *env_list)
{
	t_env_list	*var_exit_code;
	
	var_exit_code = malloc(sizeof(t_env_list));
	if (!var_exit_code)
		return ;
	var_exit_code->name = ft_strdup("?");
	var_exit_code->data = ft_strdup("0");
	add_env_list(&env_list, var_exit_code);
}