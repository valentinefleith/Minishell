/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:19 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/26 11:10:46 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "parsing.h"
# include "libft.h"
# include "minishell.h"

void execute_pipeline(t_btree *root, t_env *env, char **paths);


#endif
