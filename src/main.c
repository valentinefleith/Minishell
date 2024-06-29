/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 14:15:50 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*buffer;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		parse_user_prompt(buffer, env);
		ft_printf("%s\n", buffer);
		// rl_on_new_line();
		free(buffer);
	}
	// rl_clear_history();
}
