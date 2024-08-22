/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:33:05 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/22 18:39:40 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		i = 2;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
		}
	}
	else if (cmd[1])
	{
		i = 1;
		while (cmd[i++])
			printf("%s", cmd[i]);
		printf("\n");
	}
	return (0);
}