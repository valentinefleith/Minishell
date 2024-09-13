/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/12 17:44:57 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *envs, t_btree *tree, int	exit_status)
{
	ft_putstr_fd("exit\n", 1);
	if (tree->left->item && tree->left->item[1])
	{
		printf("bash: exit: %s: no argument required\n", tree->left->item[1]);
		exit_status = 2;
	}
	if (envs->env_list)
		envs->env_list = free_env_list(envs->env_list);
	if (envs->env_tab)
	{
		ft_free_tab(envs->env_tab);
		envs->env_tab = NULL;
	}
	if (envs)
	{
		free(envs);
		envs = NULL;
	}
	if (tree)
	{
		btree_free(tree);
		tree = NULL;	
	}
	exit(exit_status);
}
