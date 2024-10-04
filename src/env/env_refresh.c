/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_refresh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:29:46 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/03 21:27:59 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_var(t_env_list *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	*strjoin_chr(char const *s1, char const *s2, char c)
{
	char	*joined_strs;
	size_t	joined_length;

	if (!s2)
	{
		joined_strs = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
		ft_strlcpy(joined_strs, s1, ft_strlen(s1) + 1);
		joined_strs[ft_strlen(s1)] = '=';
		joined_strs[ft_strlen(s1) + 1] = '\0';
		return (joined_strs);
	}
	joined_length = 1 + ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_strs = ft_calloc(joined_length, sizeof(char));
	if (joined_strs == NULL)
		return (NULL);
	ft_strlcpy(joined_strs, s1, ft_strlen(s1) + 1);
	joined_strs[ft_strlen(s1)] = c;
	ft_strlcat(joined_strs, s2, joined_length + 1);
	return (joined_strs);
}

int	refresh_env_tab(t_env *envs)
{
	int			nb_var;
	int			i;
	t_env_list	*env_list;

	ft_free_tab(envs->env_tab);
	env_list = envs->env_list;
	nb_var = get_nb_var(env_list);
	envs->env_tab = ft_calloc(nb_var + 1, sizeof(char *));
	if (!envs->env_tab)
		return (free_env_list(envs->env_list), 1);
	i = 0;
	while (i < nb_var)
	{
		if (env_list->name)
			envs->env_tab[i] = strjoin_chr(env_list->name, env_list->data, '=');
		if (!envs->env_tab[i])
		{
			ft_free_tab(envs->env_tab);
			free_env_list(envs->env_list);
			return (1);
		}
		i++;
		env_list = env_list->next;
	}
	return (0);
}
