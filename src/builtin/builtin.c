/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 10:31:12 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_builtin builtin, t_btree *tree, char **cmd, t_env_list *env)
{
	if (builtin == PWD)
		return (ft_pwd(env));
	else if (builtin == ECHO)
		return (ft_echo(cmd));
	else if (builtin == EXIT)
		ft_exit(env, tree, 0);
	else if (builtin == ENV)
		return (ft_env(env));
	else if (builtin == CD)
		return (ft_cd(env, cmd[0]));
	else if (builtin == EXPORT)
		return (ft_export(env, cmd[0]));
	else if (builtin == UNSET)
		return (ft_unset(env, cmd));
	return (-1);
}

int	error_builtin(t_builtin builtin, char *arg)
{
	if (builtin == PWD)
		printf("Error: while getting the working directory\n");
	else if (builtin == CD)
		printf("bash: cd: %s: No such file or directory\n", arg);
	else if (builtin == EXPORT)
		printf("bash: export: '%s': is not a valid identifier\n", arg);
	else if (builtin == ENV)
	{
		printf("bash: env: No such file or directory\n");
		return (127);
	}
	else if (builtin == 7)
		printf("Error: while allocation\n");
	return (1);
}

static void	get_tab_builtin(char **tab_builtin)
{
	tab_builtin[0] = "pwd";
	tab_builtin[1] = "echo";
	tab_builtin[2] = "unset";
	tab_builtin[3] = "export";
	tab_builtin[4] = "exit";
	tab_builtin[5] = "cd";
	tab_builtin[6] = "env";
	tab_builtin[7] = NULL;
}

t_builtin	is_builtin(char *buffer)
{
	int			i;
	int			len;
	char		*tab_builtin[8];
	t_builtin	builtin;
	
	i = 0;
	len = 0;
	builtin = NONE;
	get_tab_builtin(tab_builtin);
	if (!buffer)
		return (NONE);
	while (i < NONE)
	{
		len = ft_strlen(tab_builtin[i]);
		if (ft_strncmp(buffer, tab_builtin[i], len) == 0)
		{
			builtin = i;
			break ;
		}
		else
			builtin = NONE;
		i++;
	}
	return (builtin);
}
