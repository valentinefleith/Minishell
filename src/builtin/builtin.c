/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/02 15:57:50 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_builtin builtin, t_input *input)
{
	if (builtin == PWD)
		ft_pwd();
	else if (builtin == ECHO)
		printf("%s\n", input->arg);
	else if (builtin == ECHO_N)
		printf("%s", input->arg);
}

void	ft_pwd(void)
{
	char	buffer[1024];
	
	if (getcwd(buffer, 1024) != NULL)
		printf("%s\n", buffer);
	else
		error_builtin(PWD);
}

// void	ft_cd(char *arg);
// 	printf()
// }