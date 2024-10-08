/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:38:22 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/27 13:50:22 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_pwd(void)
{
	ft_putendl_fd("Error: while getting the working directory.", 2);
	return (1);
}

int	error_cd(char *name)
{
	if (name)
		printf("bash: cd: %s: %s\n", name, strerror(errno));
	else
		printf("bash: cd: (null): %s\n", strerror(errno));
	return (1);
}

int	error_export(char *name)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": is not a valid identifier", 2);
	return (1);
}

int	error_env(void)
{
	ft_putendl_fd("bash: env: No such file or directory", 2);
	return (127);
}

int	error_exit(char *name)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (2);
}
