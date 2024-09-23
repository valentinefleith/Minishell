/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/23 12:33:47 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_token *tokens, int exit_status)
{
	if (tokens)
		ft_free_tokens(tokens);
	exit(exit_status);
}

void	exit_child_process(t_shell *shell, t_btree *tree, int exit_status)
{
	if (exit_status == -12)
		perror("fork");
	close_fd(&shell->read);
	close_fd(&shell->write);
	free_process(shell, tree);
	exit(exit_status);
}

void	free_process(t_shell *shell, t_btree *tree)
{
	if (shell->paths)
	{
		ft_free_tab(shell->paths);
		shell->paths = NULL;
	}
	if (shell->envs)
	{
		if (shell->envs->env_tab)
			ft_free_tab(shell->envs->env_tab);
		if (shell->envs->env_list)
			shell->envs->env_list = free_env_list(shell->envs->env_list);
		free(shell->envs);
		shell->envs = NULL;
	}
	if (tree)
	{
		btree_free(tree);
		tree = NULL;
	}
}

void	free_main_process(t_btree *tree)
{
	if (tree)
		btree_free(tree);
}
