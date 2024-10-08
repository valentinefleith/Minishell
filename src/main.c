/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/03 13:31:30 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_signal = 0;

static void	display_program(void)
{
	printf("                                                             \n");
	printf("\e[38;5;207m");
	printf("∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷\n");
	printf("                                                             \n");
	printf("\e[38;5;171m");
	printf(" ∷∷    ∷∷  ∷  ∷∷    ∷  ∷  ∷ ∷ ∷   ∷   ∷  ∷ ∷ ∷  ∷      ∷     \n");
	printf("\e[38;5;135m");
	printf(" ∷ ∷  ∷ ∷  ∷  ∷ ∷   ∷  ∷  ∷       ∷   ∷  ∷      ∷      ∷     \n");
	printf("\e[38;5;099m");
	printf(" ∷   ∷  ∷  ∷  ∷  ∷  ∷  ∷  ∷ ∷ ∷   ∷ ∷ ∷  ∷ ∷ ∷  ∷      ∷     \n");
	printf("\e[38;5;075m");
	printf(" ∷      ∷  ∷  ∷   ∷ ∷  ∷       ∷  ∷   ∷  ∷      ∷      ∷     \n");
	printf("\e[38;5;081m");
	printf(" ∷      ∷  ∷  ∷     ∷  ∷  ∷ ∷ ∷   ∷   ∷  ∷ ∷ ∷  ∷ ∷ ∷  ∷ ∷ ∷ \n");
	printf("                                                             \n");
	printf("\e[38;5;086m");
	printf("∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷ ∷\n");
	printf("\e[0m");
}

static t_btree	*parse_user_prompt(char *buffer, t_env *envs)
{
	t_token	*lexemes;
	t_token	*tokens;
	t_btree	*tree;

	if (!buffer)
	{
		envs = free_envs(envs);
		exit(0);
	}
	lexemes = tokenize_cmdline(buffer, envs);
	if (!lexemes)
		return (NULL);
	tokens = parser(lexemes, envs->env_list);
	lexemes = NULL;
	if (!tokens)
		return (NULL);
	tree = create_ast(tokens);
	if (tokens)
		ft_free_tokens(tokens);
	return (tree);
}

static char	*get_prompt(void)
{
	char	*buffer;

	buffer = readline("\e[35;1;3mMiniShell\e[0m \e[32;1m$> \e[0m");
	if (buffer)
		add_history(buffer);
	else
		return (free(buffer), NULL);
	return (buffer);
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
	display_program();
	while (1)
	{
		signal_monitor(false, true);
		buffer = get_prompt();
		tree = parse_user_prompt(buffer, envs);
		if (buffer)
			free(buffer);
		if (!tree)
			continue ;
		exit_status = launch_pipeline(tree, envs, get_paths(envs->env_list));
		update_exit_status(envs->env_list, exit_status);
		free_main_process(tree);
	}
	return (rl_clear_history(), exit_status);
}
