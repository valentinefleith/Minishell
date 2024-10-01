/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/01 12:39:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_token *tokens, int exit_status)
{
	if (tokens)
		ft_free_tokens(tokens);
	exit(exit_status);
}

void	free_main_process(t_btree *tree)
{
	if (tree)
		btree_free(tree);
	if (access("here_doc", F_OK) != -1)
		unlink("here_doc");
}
