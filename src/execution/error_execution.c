/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:16:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/18 15:44:28 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_execution(t_shell *shell, t_btree *tree, int exit_code)
{
	close_fd(&shell->write);
	close_fd(&shell->read);
	if (shell->pid != -1)
	{
		free_process(shell, tree);
		exit(exit_code);
	}
	if (shell->pid == -1)
		shell->pid = exit_code;
}

void	debug_exec(t_btree *tree, t_shell *shell, int index)
{
	if (!tree)
	{
		ft_putstr_fd("tree = NULL\n", 2);
		return ;	
	}
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("-----------------------------------------------------------", 2);
	print_structure(tree, 0);
	btree_print_details(tree, 0);
	
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("ID process -> ", 2);
	ft_putnbr_fd(index, 2);
	ft_putstr_fd("\n", 2);
	
	ft_putstr_fd("FD IN = ", 2);
	ft_putnbr_fd(shell->read, 2);
	ft_putstr_fd("\n", 2);
	
	ft_putstr_fd("FD OUT = ", 2);
	ft_putnbr_fd(shell->write, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("-----------------------------------------------------------", 2);
	ft_putstr_fd("\n", 2);
}
