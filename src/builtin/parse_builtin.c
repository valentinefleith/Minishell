/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:36:18 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/02 19:06:57 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tab_builtin(char **tab_builtin)
{
	tab_builtin[0] = "pwd";
	tab_builtin[1] = "echo";
	tab_builtin[2] = "echo -n";
	tab_builtin[3] = "unset";
	tab_builtin[4] = "export";
	tab_builtin[5] = "exit";
	tab_builtin[6] = "cd";
	tab_builtin[7] = NULL;
}

t_builtin	parse_builtin(char **buffer, t_input *input)
{
	int			i;
	int			len;
	char		*tab_builtin[8];
	
	i = 0;
	len = 0;
	get_tab_builtin(tab_builtin);
	if (!buffer)
		return NONE;
	while (i < NONE )
	{
		len = ft_strlen(tab_builtin[i]);
		if (ft_strncmp(buffer[0], tab_builtin[i], len) == 0)
		{
			input->builtin = i;
			input->arg = buffer[1]; // must write a function to parse arguments for builtin
			break ;
		}
		else
			input->builtin = NONE;
		i++;
	}
	return input->builtin;
}
