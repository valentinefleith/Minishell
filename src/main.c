/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/06 17:44:35 by luvallee         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	*tokens;
	t_btree	*tree;
	t_env	*envs;
	int		exit_status;
	
	(void)argc;
	(void)argv;
	envs = init_envs(env);
	while (1)
	{
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		tokens = tokenize_cmdline(buffer, envs);
		tokens = parser(tokens);
		tree = create_ast(tokens);
		if (tokens)
			ft_free_tokens(&tokens);
		exit_status = launch_pipeline(tree, envs, get_paths(envs->env_list));
		update_exit_status(envs->env_list, exit_status);
		free_main_process(buffer, tree);
	}
	return (exit_status);
}
