/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:26:03 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 10:33:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env_list *env, char **arg)
{
	t_env_list	*var;
	int		i;

	i = 0;
	while (arg[i])
	{
		var = ft_getenv(env, arg[i]);
		if (var && var->data)
		{
			free(var->data);
			var->data = NULL;
		}
		i++;
	}
	return (0);
}
