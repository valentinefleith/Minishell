/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/27 17:25:24 by vafleith         ###   ########.fr       */
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

int	execute_builtin(t_builtin builtin, t_btree *tree, bool pipeline,
		t_shell *shell)
{
	int	exit_code;
	int fd_out;

	if (check_builtin_access(tree, shell, &exit_code) != 0)
		return (exit_code);
	if (pipeline == false)
		fd_out = builtin_redirection(tree, shell);
	else
		fd_out = STDOUT_FILENO;
	if (builtin == PWD)
		exit_code = ft_pwd(shell->envs, fd_out);
	else if (builtin == ECHO)
		exit_code = ft_echo(tree->left->item, fd_out);
	else if (builtin == EXIT)
		exit_code = ft_exit(shell, tree->left->item, tree);
	else if (builtin == ENV)
		exit_code = ft_env(shell->envs->env_list, fd_out, false);
	else if (builtin == CD)
		exit_code = ft_cd(shell->envs, tree->left->item);
	else if (builtin == EXPORT)
		exit_code = ft_export(shell->envs, tree->left->item, fd_out);
	else if (builtin == UNSET)
		exit_code = ft_unset(shell->envs, tree->left->item);
	if (pipeline == false)
		free_builtin_process(shell, &exit_code);
	return (exit_code);
}

int	builtin_redirection(t_btree *tree, t_shell *shell)
{
	int	fd_out;
	
	shell->read = file_redirection(tree, shell, shell->read, INPUT);
	shell->write = file_redirection(tree, shell, shell->write, OUTPUT);
	fd_out = shell->write;
	return (fd_out);
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
		return (error_pwd());
	if (builtin == CD)
		return (error_cd(arg));
	if (builtin == EXPORT)
		return (error_export(arg));
	if (builtin == ENV)
		return (error_env());
	else if (builtin == 7)
		ft_putendl_fd("Error: while allocation\n", 2);
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
