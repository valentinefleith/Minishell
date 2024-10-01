/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:49:08 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/01 15:27:42 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "parsing.h"

typedef struct s_shell	t_shell;

void					free_and_exit(t_token *tokens, int exit_status);
void					free_process(t_shell *shell);
void					free_main_process(t_btree *tree);

void					ft_free_tab(char **strs);

t_token					*ft_free_tokens(t_token *tokens);

t_env					*free_envs(t_env *envs);

void					exit_child_process(t_shell *shell, int exit_status);

#endif
