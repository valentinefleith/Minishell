/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:19 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/05 17:36:44 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*parse_export_arg(char *arg)
{
	t_env_list	*new_var;
	int		len;
	
	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (NULL);
	len = 0;
	while (arg[len] && arg[len] != '=')
	{
		if (!ft_isalnum(arg[len]) && arg[len] != '_')
		{
			error_builtin(EXPORT, arg);
			return (NULL);
		}
		len++;
	}
	new_var->name = ft_substr(arg, 0, len);
	if (!new_var->name)
		return (NULL);
	new_var->data = ft_substr(arg, len + 1, ft_strlen(arg));
	new_var->next = NULL;
	return (new_var);
}

static int	is_arg_unique(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i == 2);
}

int	ft_export(t_env *envs, char **arg)
{
	t_env_list	*new_var;
	
	if (!arg)
		return (ft_env(envs->env_list), 0);
	if (!is_arg_unique(arg))
		return 1;
	if (!ft_isalpha(*arg[1]) && *arg[1] != '_')
		return (error_builtin(EXPORT, arg[1]));
	new_var = parse_export_arg(arg[1]);
	if (!new_var)
		return (1);
	add_env_list(&envs->env_list, new_var);
	return (refresh_env_tab(envs));
}
