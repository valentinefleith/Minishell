/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 10:34:08 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env_list *env, t_btree *tree, int	exit_status)
{
	if (env)
		env = free_env_list(&env);
	if (tree)
	{
		btree_free(tree);
		tree = NULL;	
	}
	exit(exit_status);
}
