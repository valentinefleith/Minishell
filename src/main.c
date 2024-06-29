/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/29 12:08:17 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *buffer;
	while(1)
	{
		buffer = readline("$> ");
		add_history(buffer);
		ft_printf("%s\n", buffer);
		//rl_on_new_line();
		free(buffer);
	}
	//rl_clear_history();
	ft_printf("test\n");
	ft_printf("compiled!\n");
}
