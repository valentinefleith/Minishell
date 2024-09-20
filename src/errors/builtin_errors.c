/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:38:22 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/20 13:21:35 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_pwd(void)
{
	ft_putendl_fd("Error: while getting the working directory.", 2);
	return (1);
}

int error_cd(char *name)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

int error_export(char *name)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": is not a valid identifier", 2);
	return (1);
}

int error_env(void)
{
	ft_putendl_fd("bash: env: No such file or directory", 2);
	return (127);
}
