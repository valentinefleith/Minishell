/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:52:37 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/28 15:27:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_token **tokens, int exit_status)
{
	// if (paths)
	// 	ft_free_tab(paths);
	if (tokens)
		ft_free_tokens(tokens);
	exit(exit_status);
}

static int	**free_pipe_fd(int **pipe_fd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (pipe_fd[i])
			free(pipe_fd[i]);
		pipe_fd[i] = NULL;
		i++;
	}
	if (pipe_fd)
		free(pipe_fd);
	pipe_fd = NULL;
	return (pipe_fd);
}

void	free_process(t_shell *shell, t_btree *tree)
{
	if (shell->pipe_fd)
		shell->pipe_fd = free_pipe_fd(shell->pipe_fd, shell->nb_cmd - 1);
	if (shell->paths)
	{
		ft_free_tab(shell->paths);
		shell->paths = NULL;
	}
	if (shell->envs->env_tab)
		ft_free_tab(shell->envs->env_tab);
	if (shell->envs->env_list)
		shell->envs->env_list = free_env_list(&shell->envs->env_list);
	if (tree)
	{
		btree_free(tree);
		tree = NULL;
	}
}
