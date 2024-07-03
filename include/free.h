/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:49:08 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 16:10:52 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "parsing.h"

void	ft_free_tab(char **strs);
void	free_and_exit(char **paths, int exit_status);
t_token **ft_free_tokens(t_token **tokens);

#endif
