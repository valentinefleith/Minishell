/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:26:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/20 16:35:55 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_arg_unique(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i == 2);
}

t_env_list	*ft_getenv_boost(t_env_list *env, char *name, int len)
{
	if (!env || !name)
		return (NULL);
	while (env)
	{
		if (len == (int)ft_strlen(env->name) && !ft_strncmp(env->name, name,
				len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

size_t	find_len_name(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len])
	{
		if (arg[len] == '=')
			return (len);
		if (arg[len] == '+' && arg[len + 1] == '=')
			return (len);
		if (!isalnum(arg[len]) && arg[len] != '_')
		{
			error_builtin(EXPORT, arg);
			return (-1);
		}
		len++;
	}
	return (len);
}

int	export_malloc_error(void)
{
	ft_putendl_fd("allocation failed during `export`.", 2);
	return (MALLOC_ERROR);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*cpy;

	if (src == 0 || dest == 0)
		return (dest);
	cpy = dest;
	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (cpy);
}
