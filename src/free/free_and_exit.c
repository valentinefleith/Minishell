/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/17 16:34:36 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(void *data, int exit_status)
{
	// if (paths)
	// 	ft_free_tab(paths);
	if (data)
		ft_free_tokens(data);
	exit(exit_status);
}
