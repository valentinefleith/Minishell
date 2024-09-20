/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:19 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/20 17:28:30 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_no_data(t_env *envs, char **cmd)
{
	t_env_list	*new_var;

	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (export_malloc_error());
	new_var->name = ft_strdup(cmd[1]);
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

static int	export_regular(t_env *envs, char **cmd, size_t len_name)
{
	t_env_list	*new_var;

	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (export_malloc_error());
	new_var->name = ft_substr(cmd[1], 0, len_name);
	if (!new_var->name)
	{
		free(new_var);
		return (export_malloc_error());
	}
	new_var->data = ft_substr(cmd[1], len_name + 1, ft_strlen(cmd[1]) - len_name
			- 1);
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

static int	export_existing_var(t_env_list *existing_var, char **cmd, int len)
{
	int		new_len;
	char	*new_value;

	if (cmd[1][len] == '=')
	{
		free(existing_var->data);
		existing_var->data = ft_substr(cmd[1], len + 1, ft_strlen(cmd[1])
				- len);
		if (!existing_var->data)
			return (export_malloc_error());
		return (SUCCESS);
	}
	new_len = ft_strlen(existing_var->data) + (ft_strlen(cmd[1]) - len - 2);
	new_value = malloc((1 + new_len) * sizeof(char));
	if (!new_value)
		return (export_malloc_error());
	ft_strlcpy(new_value, existing_var->data, ft_strlen(existing_var->data)
		+ 1);
	ft_strcat(new_value, cmd[1] + len + 2);
	free(existing_var->data);
	existing_var->data = new_value;
	return (SUCCESS);
}

int	ft_export(t_env *envs, char **cmd, int fd)
{
	int			len_name;
	t_env_list	*existing_var;

	if (!cmd[1])
		return (ft_env(envs->env_list, fd, true), 0);
	// TODO: fix cases 251-255
	if (!is_arg_unique(cmd))
		return (1);
	len_name = find_len_name(cmd[1]);
	if (len_name < 0)
		return (1);
	existing_var = ft_getenv_boost(envs->env_list, cmd[1], len_name);
	if (!existing_var)
	{
		if (len_name == (int)ft_strlen(cmd[1]))
			return (export_no_data(envs, cmd));
		return (export_regular(envs, cmd, len_name));
	}
	if (len_name != (int)ft_strlen(cmd[1]))
		return (export_existing_var(existing_var, cmd, len_name));
	return SUCCESS;
}

/*static t_env_list	*parse_export_arg(char *arg)
{
	t_env_list	*new_var;
	int			len;

	new_var = malloc(sizeof(t_env_list));
	if (!new_var)
		return (NULL);
	len = 0;
	while (arg[len] && arg[len] != '=')
	{
		if (!ft_isalnum(arg[len]) && arg[len] != '_')
		{
			error_builtin(EXPORT, arg);
			return (free(new_var), NULL);
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

int	ft_export(t_env *envs, char **arg, int fd)
{
	t_env_list	*new_var;

	if (!arg[1])
		return (ft_env(envs->env_list, fd, true), 0);
	if (!is_arg_unique(arg))
		return (1);
	new_var = parse_export_arg(arg[1]);
	if (!new_var)
		return (1);
	add_env_list(&envs->env_list, new_var);
	return (refresh_env_tab(envs));
}*/
