/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/02 18:06:14 by vafleith         ###   ########.fr       */
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

//void	ft_cd(char *arg)
//{
//	// si arg NULL = aller dans home
//	// sinon -> changer la variable d'env OLDPWD avec le pwd actuel et puis
//	// uitliser la fonction chdir() pour changer de repertoire
//}
//
//void	ft_exit(t_shell shell)
//{
//	// free everything and exit() with the rigth exit status
//}
