/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:19 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 11:43:39 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_no_data(t_env *envs, char *arg)
{
	t_env_list	*new_var;

	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (export_malloc_error());
	new_var->name = ft_strdup(arg);
	if (!new_var->name)
	{
		free(new_var);
		return (export_malloc_error());
	}
	new_var->data = NULL;
	new_var->next = NULL;
	add_env_list(&envs->env_list, new_var);
	return (SUCCESS);
}

static int	export_regular(t_env *envs, char *arg, size_t len_name)
{
	t_env_list	*new_var;

	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (export_malloc_error());
	new_var->name = ft_substr(arg, 0, len_name);
	if (!new_var->name)
	{
		free(new_var);
		return (export_malloc_error());
	}
	new_var->data = ft_substr(arg, len_name + 1, ft_strlen(arg) - len_name - 1);
	if (!new_var->data)
	{
		free(new_var->name);
		free(new_var);
		return (export_malloc_error());
	}
	new_var->next = NULL;
	add_env_list(&envs->env_list, new_var);
	return (SUCCESS);
}

static int	export_existing_var(t_env_list *existing_var, char *arg, int len)
{
	int		new_len;
	char	*new_value;

	if (arg[len] == '=')
	{
		free(existing_var->data);
		existing_var->data = ft_substr(arg, len + 1, ft_strlen(arg) - len);
		if (!existing_var->data)
			return (export_malloc_error());
		return (SUCCESS);
	}
	new_len = ft_strlen(existing_var->data) + (ft_strlen(arg) - len - 2);
	new_value = malloc((1 + new_len) * sizeof(char));
	if (!new_value)
		return (export_malloc_error());
	ft_strlcpy(new_value, existing_var->data, ft_strlen(existing_var->data)
		+ 1);
	ft_strcat(new_value, arg + len + 2);
	free(existing_var->data);
	existing_var->data = new_value;
	return (SUCCESS);
}

static int	perform_export(t_env *envs, char *arg)
{
	int			len_name;
	t_env_list	*existing_var;

	len_name = find_len_name(arg);
	if (len_name < 0)
		return (1);
	existing_var = ft_getenv_boost(envs->env_list, arg, len_name);
	if (!existing_var)
	{
		if (len_name == (int)ft_strlen(arg))
			return (export_no_data(envs, arg));
		return (export_regular(envs, arg, len_name));
	}
	if (len_name != (int)ft_strlen(arg))
		return (export_existing_var(existing_var, arg, len_name));
	return (SUCCESS);
}

int	ft_export(t_env *envs, char **cmd, int fd)
{
	int	i;
	int	status;

	if (!cmd[1])
		return (ft_env(envs->env_list, fd, true), 0);
	i = 1;
	while (cmd[i])
	{
		if (!isalpha(*cmd[i]) && *cmd[i] != '_')
			status = 1;
		else
			status = perform_export(envs, cmd[i]);
		if (status != SUCCESS)
		{
			error_builtin(EXPORT, cmd[i]);
			if (!*cmd[i])
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (SUCCESS);
}
