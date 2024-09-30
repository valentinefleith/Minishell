/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/30 13:12:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_token *tokens, int exit_status)
{
	if (tokens)
		ft_free_tokens(tokens);
	exit(exit_status);
}

void	exit_child_process(t_shell *shell, int exit_status)
{
	if (exit_status == -12)
		perror("fork");
	close_fd(&shell->read);
	close_fd(&shell->prev_read);
	close_fd(&shell->write);
	ft_putnbr_fd(shell->read, 2);
	ft_putendl_fd(" read", 2);
	ft_putnbr_fd(shell->prev_read, 2);
	ft_putendl_fd(" prevread", 2);
	ft_putnbr_fd(shell->write, 2);
	ft_putendl_fd(" write", 2);
	free_process(shell);
	exit(exit_status);
}

void	free_process(t_shell *shell)
{
	if (shell->paths)
	{
		ft_free_tab(shell->paths);
		shell->paths = NULL;
	}
	if (shell->envs)
		shell->envs = free_envs(shell->envs);
	btree_free(shell->main_root);
	shell->main_root = NULL;
}

void	free_main_process(t_btree *tree)
{
	if (tree)
		btree_free(tree);
	if (access("here_doc", F_OK) != -1)
		unlink("here_doc");
}
