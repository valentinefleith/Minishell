/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/26 10:25:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_env_list *env_list)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (env_list)
	{
		seeking = ft_strncmp(env_list->name, "PATH", 4);
		if (!seeking)
			break ;
		env_list = env_list->next;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(env_list->data + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
}

t_env* init_envs(char **env)
{
	t_env_list *env_list;
	char **env_tab;
	t_env *envs;
	
	envs = malloc(sizeof(t_env));
	if (!envs)
		return NULL;
	env_tab = ft_strsdup(env);
	if (!env_tab)
	{
		return NULL;
	}
	env_list = NULL;
	env_list = build_env_list(env_list, env);
	envs->env_list = env_list;
	envs->env_tab = env_tab;
	return envs;
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	*tokens;
	t_btree	*tree;
	char **paths;
	t_env*	envs;

	(void)argc;
	(void)argv;
	envs = init_envs(env);
	paths = get_paths(envs->env_list);
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
		{
			continue;
			free(buffer);
		}
		tokens = parser(tokens, envs->env_list);
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
	envs->env_list = free_env_list(&(envs->env_list));
}
