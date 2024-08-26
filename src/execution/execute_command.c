/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:22:14 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/26 14:31:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_no_env(char *cmd_name)
{
	/*if (access(cmd_name, F_OK) != 0)
	{
		if (ft_strchr(cmd_name, '/'))
			no_such_file(cmd_name);
		else
			cmd_not_found(cmd_name);
		return (NULL);
	}
	if (access(cmd_name, X_OK) != 0)
	{
		permission_denied(cmd_name);
		return (NULL);
	}*/
	return (ft_strdup(cmd_name));
}

static char	*get_path_env(char *cmd_name, char **paths)
{
	char	*cmd_attempt;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_attempt = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!cmd_attempt)
			return (NULL);
		if (access(cmd_attempt, F_OK) == 0)
		{
			if (access(cmd_attempt, X_OK) == 0)
				return (cmd_attempt);
			//permission_denied(cmd_name);
		}
		free(cmd_attempt);
		i++;
	}
	return (get_path_no_env(cmd_name));
}
static char *get_full_cmd_path(char *command_name, char **paths)
{
	char	*executable_path;

	if (ft_strchr(command_name, '/') || !paths)
		executable_path = get_path_no_env(command_name);
	else
		executable_path = get_path_env(command_name, paths);
	/*if (!executable_path)
	{
		if (command_name && ft_strnstr(command_name, "./", 2))
		{
			ft_free_tab(command_name);
			free_and_exit(paths, 126);
		}
		ft_free_tab(cmd.cmd_and_args);
		free_and_exit(paths, 127);
	}*/
	return (executable_path);
}


static void execute_single_command(t_btree *node, t_env *envs, char **paths)
{
	char *full_cmd_path;
	int status;

	if (node->type != COMMAND)
		return;
	pid_t pid = fork();
	if (pid == 0)
	{
		t_builtin builtin_type = is_builtin(node->left->item[0]);
		if (builtin_type != NONE)
		{
			execute_builtin(builtin_type, node, node->left->item, envs);
			return;
		}
		full_cmd_path = get_full_cmd_path(node->left->item[0], paths);
		execve(full_cmd_path, node->left->item, envs->env_tab);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

void execute_pipeline(t_btree *root, t_env *envs, char **paths)
{
	// base case
	if (root->type == COMMAND)
		return execute_single_command(root, envs, paths);
	// recursive part
	execute_single_command(root->left, envs, paths);
	return execute_pipeline(root->right, envs, paths);
}

