/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:31 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/20 16:08:00 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*update_data(t_env_list **env_var, char *new_data)
{
	if (*env_var)
	{
		free((*env_var)->data);
		return (ft_strdup(new_data));
	}
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
	ft_putstr_fd("\e[31mbash: cd: too many arguments\e[0m\n", 2);
	return (1);
}

int	ft_cd(t_env *envs, char **cmd)
{
	t_env_list	*oldpwd;
	t_env_list	*pwd;
	char		buffer[1024];
	char		*path;

	oldpwd = ft_getenv(envs->env_list, "OLDPWD");
	pwd = ft_getenv(envs->env_list, "PWD");
	if (!oldpwd || !pwd)
		return (1);
	if (!is_arg_unique_cd(cmd))
		return (cd_error());
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("\e[31mbash: cd: HOME not set\e[0m\n", 2), 1);
	}
	else
		path = cmd[1];
	oldpwd->data = update_data(&oldpwd, pwd->data);
	if (chdir(path) != 0)
		return (error_builtin(CD, path));
	pwd->data = update_data(&pwd, getcwd(buffer, 1023));
	if (!pwd->data)
		return (1);
	return (refresh_env_tab(envs));
}
