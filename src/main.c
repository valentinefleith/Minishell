/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/14 17:59:35 by luvallee         ###   ########.fr       */
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
	t_env	*env_list;

	(void)argc;
	(void)argv;
	(void)tree;
	tokens = NULL;
	buffer = NULL;
	env_list = NULL;
	while (1)
	{
		// ft_printf("$> ");
		// buffer = get_next_line(0);
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		if (ft_strlen(buffer) == 4 && !ft_strncmp(buffer, "exit", 4))
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		env_list = build_env_list(env_list, env);
		tokens = tokenize_cmdline(buffer);
		tree = NULL;
		tokens = parser(tokens, env_list);
		debug_print_stack(tokens, "INPUT for tree");
		printf("\n");
		if (tokens)
			ft_free_tokens(&tokens);
		free(buffer);
	}
}
