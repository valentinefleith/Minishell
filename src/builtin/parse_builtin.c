/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:36:18 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/21 17:56:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tab_builtin(char **tab_builtin)
{
	tab_builtin[0] = "pwd";
	tab_builtin[1] = "echo";
	tab_builtin[2] = "unset";
	tab_builtin[3] = "export";
	tab_builtin[4] = "exit";
	tab_builtin[5] = "cd";
	tab_builtin[6] = "env";
	tab_builtin[7] = NULL;
}

t_builtin	is_builtin(char *buffer)
{
	int			i;
	int			len;
	char		*tab_builtin[8];
	t_builtin	builtin;
	
	i = 0;
	len = 0;
	builtin = NONE;
	get_tab_builtin(tab_builtin);
	if (!buffer)
		return NONE;
	while (i < NONE)
	{
		len = ft_strlen(tab_builtin[i]);
		if (ft_strncmp(buffer, tab_builtin[i], len) == 0)
		{
			builtin = i;
			break ;
		}
		else
			builtin = NONE;
		i++;
	}
	return (builtin);
}
