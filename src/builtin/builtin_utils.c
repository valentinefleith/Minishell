/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:26:11 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/02 22:27:04 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
