/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:46:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/23 15:37:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_envs(char **env)
{
	t_env_list	*env_list;
	char		**env_tab;
	t_env		*envs;

	if (!env)
		return (NULL);
	envs = malloc(sizeof(t_env));
	if (!envs)
		return (NULL);
	env_list = NULL;
	env_list = build_env_list(env_list, env);
	if (add_exit_status_var(env_list) == MALLOC_ERROR)
	{
		free(envs);
		free_env_list(env_list);
		return (NULL);
	}
	env_tab = ft_strsdup(env);
	envs->env_list = env_list;
	envs->env_tab = env_tab;
	return (envs);
}

t_env_list	*build_env_list(t_env_list *env_list, char **src_env)
{
	int			i;
	int			limit;
	t_env_list	*new;

	i = 0;
	while (src_env[i])
	{
		limit = ft_get_index(src_env[i], '=');
		new = malloc(sizeof(t_env_list));
		if (!new)
			return (free_env_list(env_list));
		new->name = ft_substr(src_env[i], 0, limit);
		new->data = ft_substr(src_env[i], limit + 1, ft_strlen(src_env[i]));
		if (!new->name || !new->data)
		{
			if (new->name)
				free(new->name);
			if (new->data)
				free(new->data);
			return (free_env_list(env_list));
		}
		new->next = NULL;
		add_env_list(&env_list, new);
		i++;
	}
	return (env_list);
}

/*
 * /!\ WARNING dans cette fonction l'alloc peut fail
 * (a verifier au moment de l'exex) */

void	update_exit_status(t_env_list *env_list, int exit_status)
{
	t_env_list	*var_status;

	var_status = ft_getenv(env_list, "?");
	if (!var_status)
		return ;
	if (var_status->data)
		free(var_status->data);
	if (g_signal != 0)
	{
		var_status->data = ft_itoa(g_signal);
		g_signal = 0;
	}
	else
		var_status->data = ft_itoa(exit_status);
}

int	add_exit_status_var(t_env_list *env_list)
{
	t_env_list	*var_exit_code;

	var_exit_code = malloc(sizeof(t_env_list));
	if (!var_exit_code)
		return (MALLOC_ERROR);
	var_exit_code->name = ft_strdup("?");
	if (!var_exit_code->name)
	{
		free(var_exit_code);
		return (MALLOC_ERROR);
	}
	var_exit_code->data = ft_strdup("0");
	if (!var_exit_code->data)
	{
		free(var_exit_code->name);
		free(var_exit_code);
		return (MALLOC_ERROR);
	}
	var_exit_code->next = NULL;
	add_env_list(&env_list, var_exit_code);
	return (0);
}
