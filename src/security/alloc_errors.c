/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:51:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/12 18:42:58 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_error(char *name)
{
	ft_putstr_fd("allocation failed for :", 2);
	ft_putendl_fd(name, 2);
	if (!ft_strncmp(name, "envs", 40))
		exit(1);
}
