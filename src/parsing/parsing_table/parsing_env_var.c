/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:50 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/22 17:10:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_env_var(t_token *output, t_env *env)
{
	char	*new_arg;
	size_t	len;
	int		i;
	
	while (output)
	{
		i = 0;
		new_arg = NULL;
		while (output->arg && output->arg[i])
		{
			if (search_env_var(env, output->arg[i]))
			{
				len = get_new_arg_len(env, output->arg[i]);
				new_arg = malloc(sizeof(char *) * len + 1);
				if (!new_arg)
					return ;
				new_arg = do_expansion_var(env, output->arg[i], new_arg);
				if (output->arg[i])
					free(output->arg[i]);
				output->arg[i] = new_arg;
			}
			i++;
		}
		output = output->next;
	}
}

t_env	*search_env_var(t_env *env, char *arg)
{
	char	*name;
	t_env	*env_var;
	
	if (!env || !arg)
		return (NULL);
	name = NULL;
	while (*arg)
	{
		if (*arg == '$')
		{
			name = get_var_name(arg);
			env_var = ft_getenv(env, name);
			if (env_var)
				return (free(name), env_var);
		}
		arg++;
	}
	if (name)
		free(name);
	return (NULL);
}

char	*do_expansion_var(t_env *env, char *arg, char *new_arg)
{
	t_env	*var;
	size_t	len;

	len = 0;
	while (*arg)
	{
		if (*arg == '$')
		{
			var = search_env_var(env, arg);
			if (var)
			{
				ft_memcpy(&new_arg[len], var->data, ft_strlen(var->data));
				len += ft_strlen(var->data);
				while (*arg && !ft_isblank(*arg))
					arg++;
			}
		}
		else
		{
			ft_memcpy(&new_arg[len], arg, 1);
			arg++;
			len++;
		}
	}
	return (new_arg);
}

int	get_new_arg_len(t_env *env, char *arg)
{
	t_env	*var;
	size_t	len;
	
	if (!arg)
		return (0);
	len = 0;
	while (*arg)
	{
		if (*arg == '$')
		{
			var = search_env_var(env, arg);
			if (var)
			{
				len += ft_strlen(var->data);
				while (*arg && !ft_isblank(*arg))
					arg++;
			}
		}
		else
		{
			len++;
			arg++;	
		}
	}
	return (len);
}

char	*get_var_name(char *arg)
{
	char	*name;
	int		i;
	
	if (!arg)
		return (NULL);
	name = NULL;
	i = 1;
	while (arg[i] && !ft_isblank(arg[i])
		&& arg[i] != SINGLE_QUOTE && arg[i] != DOUBLE_QUOTE)
		i++;
	name = ft_substr(arg, 1, i - 1);
	return (name);
}
