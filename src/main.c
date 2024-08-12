/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 15:29:37 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "parsing.h"
#include "free.h"


int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	*tokens;
	t_btree	*tree;

	(void)argc;
	(void)argv;
	(void)env;
	(void)tree;
	tokens = NULL;
	buffer = NULL;
	while (1)
	{
		// ft_printf("$> ");
		// buffer = get_next_line(0);
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		if (ft_strlen(buffer) == ft_strlen("exit") && !ft_strncmp(buffer,
				"exit", 4))
		{
			free(buffer);
			// if (tokens)
			// 	ft_free_tokens(&tokens);
			exit(EXIT_SUCCESS);
		}
		tokens = tokenize_cmdline(buffer);
		ft_print_token_types(tokens);
		tree = NULL;
		tokens = parser(tokens);
		debug_print_stack(tokens, "STACK FINAL");
		if (tokens)
			ft_free_tokens(&tokens);
		free(buffer);
	}
}
