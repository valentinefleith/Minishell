/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/19 11:17:48 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, t_btree *tree, int	exit_status)
{
	ft_putstr_fd("process exited.\n", 1);
	if (tree->left->item && tree->left->item[1])
	{
		printf("bash: exit: %s: no argument required\n", tree->left->item[1]);
		exit_status = 2;
	}
	if (shell->envs->env_list)
		shell->envs->env_list = free_env_list(shell->envs->env_list);
	if (shell->envs->env_tab)
	{
		ft_free_tab(shell->envs->env_tab);
		shell->envs->env_tab = NULL;
	}
	if (shell->envs)
	{
		free(shell->envs);
		shell->envs = NULL;
	}
	if (tree)
	{
		btree_free(tree);
		tree = NULL;	
	}
	ft_free_tab(shell->paths);
	exit(exit_status);
}
