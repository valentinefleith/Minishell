/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/19 14:52:09 by luvallee         ###   ########.fr       */
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

int				g_signal = 0;

static t_btree	*parse_user_prompt(char *buffer, t_env *envs)
{
	t_token	*lexemes;
	t_token	*tokens;
	t_btree	*tree;

	if (!buffer)
		return (NULL);
	lexemes = tokenize_cmdline(buffer, envs);
	if (!lexemes)
	{
		alloc_error("lexer");
		return (NULL);
	}
	tokens = parser(lexemes);
	if (!tokens)
	{
		// if (lexemes)
		// 	lexemes = ft_free_tokens(lexemes);
		return (NULL);
	}
	tree = create_ast(tokens);
	if (tokens)
		ft_free_tokens(tokens);
	return (tree);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_env	*envs;
	int		exit_status;
	t_btree	*tree;

	(void)argc;
	(void)argv;
	envs = init_envs(env);
	if (!envs)
		alloc_error("envs");
	while (1)
	{
		signal_monitor(false, true);
		buffer = readline("\e[32;1mMiniShell$> \e[0m");
		add_history(buffer);
		tree = parse_user_prompt(buffer, envs);
		if (buffer)
			free(buffer);
		if (!tree)
			continue ;
		exit_status = launch_pipeline(tree, envs, get_paths(envs->env_list));
		update_exit_status(envs->env_list, exit_status);
		free_main_process(tree);
	}
	return (exit_status);
}
