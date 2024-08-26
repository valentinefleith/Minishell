/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:31 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 11:29:33 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_cd(t_env *envs, char *path)
{
	t_env_list	*oldpwd;
	t_env_list	*pwd;
	char	buffer[1024];
	
	oldpwd = ft_getenv(envs->env_list, "OLDPWD");
	pwd = ft_getenv(envs->env_list, "PWD");
	if (!oldpwd || !pwd)
		return (1);
	if (!path || ft_strlen(path) == 0)
	{
		path = getenv("HOME");
		if (!path)
			return (printf("bash: cd: HOME not set\n"), 1);
	}
	else if (!ft_strncmp(path, "-", 1) && ft_strlen(path) == 1)
		path = getenv("OLDPWD");
	oldpwd->data = update_data(&oldpwd, pwd->data);
	if (chdir(path) != 0)
		return (error_builtin(CD, path));
	pwd->data = update_data(&pwd, getcwd(buffer, 1023));
	if (!pwd->data)
		return (1);
	return refresh_env_tab(envs);
	//return (0);
}
