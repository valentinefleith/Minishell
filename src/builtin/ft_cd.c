/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:31 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/25 15:02:18 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*update_data(t_env_list **env_var, char *new_data)
{
	if (*env_var && (*env_var)->data)
		free((*env_var)->data);
	if (!new_data)
		return (error_cd(".."), NULL);
	else
		return (ft_strdup(new_data));
	return (NULL);
}

static int	is_arg_unique_cd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i <= 2);
}

static int	cd_error(void)
{
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
	return (1);
}

static char	*cd_home(t_env_list *env_list)
{
	t_env_list	*var_home;

	if (!env_list)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (NULL);
	}
	var_home = NULL;
	var_home = ft_getenv(env_list, "HOME");
	if (!var_home || (var_home && !var_home->data))
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (NULL);
	}
	else if (var_home && var_home->data)
		return (var_home->data);
	return (NULL);
}

int	ft_cd(t_env *envs, char **cmd)
{
	t_env_list	*oldpwd;
	t_env_list	*pwd;
	char		buffer[1024];
	char		*path;

	if (!cmd[1])
		path = cd_home(envs->env_list);
	else
		path = cmd[1];
	oldpwd = ft_getenv(envs->env_list, "OLDPWD");
	pwd = ft_getenv(envs->env_list, "PWD");
	if (!oldpwd || !pwd)
		return (1);
	if (!is_arg_unique_cd(cmd))
		return (cd_error());
	oldpwd->data = update_data(&oldpwd, pwd->data);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (error_builtin(CD, path));
	pwd->data = update_data(&pwd, getcwd(buffer, 1023));
	if (!pwd->data)
		return (1);
	return (refresh_env_tab(envs));
}
