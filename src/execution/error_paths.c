/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:08:13 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/22 18:05:20 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_such_file(char *filename)
{
	ft_putstr_fd("bash: ", 2);
	if (filename)
		ft_putendl_fd(filename, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
}

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: ", 2);
	if (cmd_name)
		ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	permission_denied(char *name)
{
	ft_putstr_fd("bash: ", 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(": permission denied\n", 2);
}

void	is_directory(char *name)
{
	ft_putstr_fd("bash: ", 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(": is a directory\n", 2);
}