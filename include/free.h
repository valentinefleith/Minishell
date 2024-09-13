/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:49:08 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/06 16:34:26 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "parsing.h"

typedef struct s_shell t_shell;

void	free_and_exit(t_token *tokens, int exit_status);
void	free_process(t_shell *shell, t_btree *tree);
void	free_main_process(t_btree *tree);

void	ft_free_tab(char **strs);

t_token	*ft_free_tokens(t_token *tokens);

void	exit_child_process(t_shell *shell, t_btree *tree, int exit_status);

#endif
