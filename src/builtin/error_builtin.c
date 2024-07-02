/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:57:26 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/02 15:47:06 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_builtin(t_builtin builtin)
{
	if (builtin == PWD)
	{
		printf("Error: while getting th working directory\n");
		// faut il exit ou continuer l'execution ?
	}
	else if (builtin == 7)
		printf("Error: while allocation\n");
}