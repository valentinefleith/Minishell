/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:16:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/30 16:19:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_execution(t_shell *shell, int exit_code)
{
	close_fd(&shell->write);
	close_fd(&shell->read);
	if (shell->pid != -1)
	{
		free_process(shell);
		exit(exit_code);
	}
	if (shell->pid == -1)
		shell->pid = exit_code;
}

void	debug_exec(t_btree *tree, t_shell *shell, int index)
{
	(void)tree;
	(void)index;
	// if (!tree)
	// {
	// 	ft_putstr_fd("tree = NULL\n", 2);
	// 	return ;	
	// }
	ft_putendl_fd("-----------------------------------------------------------", 1);
	// print_structure(tree, 0);
	// btree_print_details(tree, 0);
	
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd(" <- ID process", 1);
	ft_putstr_fd("\n", 1);
	
	ft_putnbr_fd(shell->read, 1);
	ft_putendl_fd(" = FD IN", 1);
	
	ft_putnbr_fd(shell->write, 1);
	ft_putendl_fd(" = FD OUT ", 1);
	ft_putendl_fd("-----------------------------------------------------------", 1);
}
