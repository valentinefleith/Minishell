/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:34:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 10:31:52 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_list *env)
{
	if (!env)
		return (1);
	if (ft_getenv(env, "PATH")->data == NULL)
		return (error_builtin(ENV, NULL));
	while (env)
	{
		if (env->name && env->data)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->data, 1);
			ft_putstr_fd("\n", 1);
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
		if (len == ft_strlen(env->name) && !ft_strncmp(env->name, name, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}
