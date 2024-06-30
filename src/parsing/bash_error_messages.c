/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_error_messages.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:08:13 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/30 20:46:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_such_file(char *filename)
{
	ft_putstr_fd("bash: no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
}

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
}

void	permission_denied(char *name)
{
	ft_putstr_fd("bash: permission denied: ", 2);
	ft_putendl_fd(name, 2);
}
