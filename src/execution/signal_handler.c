/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:14:41 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/23 16:14:04 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("^C\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 130;
	}
	if (signal == SIGQUIT)
		return ;
}

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_signal = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)", 2);
		ft_putstr_fd("\n", 2);
		g_signal = 131;
	}
}

void	signal_monitor(bool child_process, bool interaction_mode)
{
	rl_catch_signals = 0;
	if (child_process == false && interaction_mode == true)
	{
		signal(SIGINT, &handle_signal_interactive);
		signal(SIGQUIT, &handle_signal_interactive);
	}
	else if (child_process == false && interaction_mode == false)
	{
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, &handle_signal);
	}
	else if (child_process == true && interaction_mode == false)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

// void	signal_monitor_interactive(t_env_list *env_list)
// {
// 	struct sigaction act;
	
// 	rl_catch_signals = 0;
// 	ft_bzero(&act, sizeof(act));
// 	act.sa_handler = &handle_signal_interactive;
// 	sigemptyset(&act.sa_mask);
// 	act.sa_flags = 0;
// 	sigaction(SIGINT, &act, NULL);
// }

// void	signal_monitor(bool child_process)
// {
// 	struct sigaction act;
	
// 	rl_catch_signals = 0;
// 	ft_bzero(&act, sizeof(act));
// 	if (child_process == true)
// 	{
// 		rl_catch_signals = 0;
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 	}
// 	else
// 	{
// 		act.sa_handler = &handle_signal;
// 		act.sa_flags = 0;
// 		sigemptyset(&act.sa_mask);
// 		sigaction(SIGINT, &act, NULL);
// 		sigaction(SIGQUIT, &act, NULL);
// 	}
// }
