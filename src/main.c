/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/17 17:17:28 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	**tokens;
	t_btree	*tree;

	// t_cmd	cmd;
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
		tokens = tokenize_cmdline(buffer);
		tree = create_ast(*tokens);
		// tree = test_tree();
		print_structure(tree, 0);
		// ft_print_token_types(*tokens);
		// execute_command(cmd, env);
		// ft_printf("%s\n", buffer);
		// rl_on_new_line();
		free(buffer);
	}
	// rl_clear_history();
}
