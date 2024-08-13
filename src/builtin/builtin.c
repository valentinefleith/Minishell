/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/13 16:15:43 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit()
{
	// free everything and exit() with the rigth exit status ?
	exit(EXIT_SUCCESS);
}

void	execute_builtin(t_builtin builtin, char *arg, bool option)
{
	if (builtin == PWD)
		ft_pwd();
	else if (builtin == ECHO)
		ft_echo(arg, option);
	else if (builtin == EXIT)
		ft_exit();
}

void	ft_pwd(void)
{
	char	buffer[1024];
	
	if (getcwd(buffer, 1024) != NULL)
		printf("%s\n", buffer);
	else
		error_builtin(PWD);
}

void	ft_echo(char *arg, bool option)
{
	if (option == true)
	{
		if (!arg)
			return ;
		else
			printf("%s", arg);
	}
	else if (arg)
		printf("%s\n", arg);
}

void	ft_cd(char *arg)
{
	// si arg NULL = aller dans home
	if (!arg)
		chdir(getenv("HOME"));
	else
	{
		// sinon -> changer la variable d'env OLDPWD avec le pwd actuel et puis
		// uitliser la fonction chdir() pour changer de repertoire
		// puis changer la variable d'env PWD avec le nouveau pwd ?
	}
}

void	ft_export()
{
	// si pas d'argument afficher la liste des variables d'env
	
	// sinon verifier si l'arg match avec les regles de grammaires, si la var
	//existe deja, 
	
	// ou ajouter une variable d'env si pas de valeur precisee 
	// sinon modifier la valeur dune variable d'env
	//
}

// void	ft_unset()


