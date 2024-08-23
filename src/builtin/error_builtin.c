/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:57:26 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/23 13:28:37 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_builtin(t_builtin builtin, char *arg)
{
	if (builtin == PWD)
		printf("Error: while getting the working directory\n");
	else if (builtin == CD)
		printf("bash: cd: %s: No such file or directory\n", arg);
	else if (builtin == EXPORT)
		printf("bash: export: '%s': is not a valid identifier\n", arg);
	else if (builtin == 7)
		printf("Error: while allocation\n");
	return (1);
}
