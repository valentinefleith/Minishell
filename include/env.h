/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:58:36 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/26 11:48:58 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "builtin.h"
# include "minishell.h"

/************************ Env ************************************************/

t_env_list	*build_env_list(t_env_list *env, char **src_env);
t_env		*init_envs(char **env);
void		print_env_list(t_env_list *env);
int			refresh_env_tab(t_env *envs);

void		add_env_list(t_env_list **list, t_env_list *new);
t_env_list	*free_env_list(t_env_list **list);

#endif
