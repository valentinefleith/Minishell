/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:16 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/22 18:41:43 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit()
{
	// free everything and exit() with the rigth exit status ?
	exit(EXIT_SUCCESS);
}

void	execute_builtin(t_builtin builtin, char **cmd, t_env *env)
{
	if (builtin == PWD)
		ft_pwd(env);
	else if (builtin == ECHO)
		ft_echo(cmd);
	else if (builtin == EXIT)
		ft_exit();
	else if (builtin == ENV)
		ft_env(env);
}

// void	ft_export()
// {
// 	// si pas d'argument afficher la liste des variables d'env
	
// 	// sinon verifier si l'arg match avec les regles de grammaires, si la var
// 	//existe deja, 
	
// 	// ou ajouter une variable d'env si pas de valeur precisee 
// 	// sinon modifier la valeur dune variable d'env
// 	//
// }

// void	ft_unset()
