/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:51:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/12 16:01:04 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void alloc_error(char *name)
{
	ft_putstr_fd("allocation failed for :", 2);
	ft_putendl_fd(name, 2);
	exit(1);
}
