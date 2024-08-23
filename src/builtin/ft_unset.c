/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:26:03 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/23 15:12:32 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env *env, char **arg)
{
	t_env	*var;
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
