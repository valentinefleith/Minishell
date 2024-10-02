/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:34:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/26 17:48:32 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_error(t_env_list *env)
{
	if (env && env->name && !ft_strncmp(env->name, "?", 1))
		return (1);
	if (ft_getenv(env, "PATH") == NULL)
		return (error_builtin(ENV, NULL), 1);
	return (0);
}

// a terme on pourra peut etre print a partir du tableau ca ferait moins d'operations
int	ft_env(t_env_list *env, int fd, bool option)
{
	if (!env || env_error(env) == 1)
		return (1);
	while (env)
	{
		if (env->name)
		{
			if (option)
				ft_putstr_fd("export ", fd);
			if (env->data || option)
				ft_putstr_fd(env->name, fd);
			if (env->data)
			{
				ft_putstr_fd("=", fd);
				if (option)
					ft_putstr_fd("\"", fd);
				ft_putstr_fd(env->data, fd);
				if (option)
					ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
	return (0);
}

t_env_list	*ft_getenv(t_env_list *env, char *name)
{
	size_t	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	while (env)
	{
		if (env && env->name)
		{
			if (len == ft_strlen(env->name) && !ft_strncmp(env->name, name,
					len))
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}
