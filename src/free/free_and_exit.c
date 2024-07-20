/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/20 13:25:05 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_token **tokens, int exit_status)
{
	// if (paths)
	// 	ft_free_tab(paths);
	if (tokens)
		ft_free_tokens(tokens);
	exit(exit_status);
}
