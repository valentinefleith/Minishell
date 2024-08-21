/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/21 15:27:11 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **env)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (*env)
	{
		seeking = ft_strncmp(*env, "PATH", 4);
		if (!seeking)
			break ;
		env++;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(*env + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	*tokens;
	t_btree	*tree;
	char **paths;

	(void)argc;
	(void)argv;
	paths = get_paths(env);
	// check malloc paths etc.
	while (1)
	{
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
		if (tokens == NULL)
			continue;
		// ft_print_token_types(tokens);
		tokens = parser(tokens);
		// debug_print_stack(tokens, "STACK FINAL");
		tree = create_ast(tokens);
		// print_structure(tree, 0);
		// btree_print_details(tree, 1);
		execute_pipeline(tree, env, paths);
		if (tokens)
			ft_free_tokens(&tokens);
		if (tree)
			btree_free(tree);
		free(buffer);
	}
}
