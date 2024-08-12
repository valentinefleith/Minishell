/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/12 20:13:32 by vafleith         ###   ########.fr       */
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
			exit(EXIT_SUCCESS);
		}
		tokens = tokenize_cmdline(buffer);
		ft_print_token_types(tokens);
		tokens = parser(tokens);
		debug_print_stack(tokens, "STACK FINAL");
		tree = create_ast(tokens);
		print_structure(tree, 0);
		btree_print_details(tree, 1);
		if (tokens)
			ft_free_tokens(&tokens);
		if (tree)
			btree_free(tree);
		free(buffer);
	}
}
