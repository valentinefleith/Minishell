/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:21:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/02 17:39:35 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *envs, int fd)
{
	char	*path;
	char	buffer[1024];

	if (!envs->env_list)
		return (-1);
	path = getcwd(buffer, 1024);
	if (path)
		ft_putendl_fd(path, fd);
	else
		return (error_builtin(PWD, NULL));
	return (0);
}
