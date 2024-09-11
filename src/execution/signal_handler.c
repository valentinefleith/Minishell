/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:14:41 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/11 11:56:53 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	signal_handler(int signal)
{
	if (signal == SIGINT)
}

void	signal_monitor(void)
{
	struct sigaction act;

	act.sa_handler = &signal_handler;
}
