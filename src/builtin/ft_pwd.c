/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:21:54 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 10:33:01 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env_list *env)
{
	t_env_list	*path;
	
	if (!env)
		return (-1);
	path = ft_getenv(env, "PWD");
	if (path)
		printf("%s\n",path->data);
	else
		return (error_builtin(PWD, NULL));
	return (0);
}
