/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/20 13:23:07 by luvallee         ###   ########.fr       */
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
		if (!ft_strncmp(buffer, "exit", 4))
		{
			free_and_exit(tokens, EXIT_SUCCESS);
			free(buffer);
		}
		tokens = tokenize_cmdline(buffer);
		// ft_print_lexing(*tokens);
		// ft_print_token_types(*tokens);
		parser(tokens, NULL);
		(void)tree;
		//cmd = parse_user_prompt(buffer, env);
		// execute_command(cmd, env);
		// ft_printf("%s\n", buffer);
		free(buffer);
	}
	// rl_clear_history();
}
