/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:19 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/23 14:21:25 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*parse_export_arg(char *arg)
{
	t_env	*new_var;
	int		len;
	
	new_var = malloc(sizeof(t_env));
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

int	ft_export(t_env *env, char *arg)
{
	t_env	*new_var;
	
	if (!arg)
		return (ft_env(env), 0);
	else if (!ft_isalpha(*arg) && *arg != '_')
		return (error_builtin(EXPORT, arg));
	new_var = parse_export_arg(arg);
	if (!new_var)
		return (1);
	add_env_list(&env, new_var);
	return (0);
}