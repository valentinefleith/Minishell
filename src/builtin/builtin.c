/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/20 12:49:27 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtin_access(t_btree *tree, t_shell *shell, int *exit_code)
{
	if (ft_strchr(tree->left->item[0], '/'))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tree->item[0], 2);
		ft_putstr_fd(": No such file or directory.\n", 2);
		*exit_code = 127;
		free_builtin_process(shell, exit_code);
		return (*exit_code);
	}
	return (0);
}

int	execute_builtin(t_builtin builtin, t_btree *tree, char **cmd, t_shell *shell)
{
	int	exit_code;
	
	if (check_builtin_access(tree, shell, &exit_code) != 0)
		return (exit_code);
	shell->read = file_redirection(tree, shell, shell->read, INPUT);
	shell->write = file_redirection(tree, shell, shell->write, OUTPUT);
	if (builtin == PWD)
		exit_code = ft_pwd(shell->envs, shell->write);
	else if (builtin == ECHO)
		exit_code = ft_echo(cmd, shell->write);
	else if (builtin == EXIT)
		ft_exit(shell, tree, 0);
	else if (builtin == ENV)
		exit_code = ft_env(shell->envs->env_list);
	else if (builtin == CD)
		exit_code = ft_cd(shell->envs, cmd);
	else if (builtin == EXPORT)
		exit_code = ft_export(shell->envs, cmd);
	else if (builtin == UNSET)
		exit_code = ft_unset(shell->envs, cmd);
	free_builtin_process(shell, &exit_code);
	return (exit_code);
}

void	free_builtin_process(t_shell *shell, int *exit_code)
{
	close_fd(&shell->read);
	close_fd(&shell->write);
	ft_free_tab(shell->paths);
	if (shell->pid != -1)
		*exit_code = shell->pid;
}

int	error_builtin(t_builtin builtin, char *arg)
{
	if (builtin == PWD)
		return error_pwd();
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

t_builtin	is_builtin(char *maybe_builtin)
{
	int			i;
	size_t		len;
	char		*tab_builtin[8];
	t_builtin	builtin;
	
	i = 0;
	len = 0;
	builtin = NONE;
	get_tab_builtin(tab_builtin);
	if (!maybe_builtin)
		return (NONE);
	while (i < NONE)
	{
		len = ft_strlen(tab_builtin[i]);
		if (ft_strncmp(maybe_builtin, tab_builtin[i], len) == 0
			&& len == ft_strlen(maybe_builtin))
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
