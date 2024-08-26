/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 11:59:30 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *envs, t_btree *tree, int	exit_status)
{
	if (envs->env_list)
		envs->env_list = free_env_list(&envs->env_list);
	if (envs->env_tab)
	{
		ft_free_tab(envs->env_tab);
		envs->env_tab = NULL;
	}
	free(envs);
	if (tree)
	{
		btree_free(tree);
		tree = NULL;	
	}
	exit(exit_status);
}
