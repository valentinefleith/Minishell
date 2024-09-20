/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:58:13 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/20 12:47:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

void	alloc_error(char *name);
t_token	*check_file_error(t_token *tokens, t_env *envs);

// BUILTINS


int error_pwd(void);

#endif
