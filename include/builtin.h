/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/21 16:22:14 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <stdbool.h>

typedef enum e_builtin
{
	PWD, 
	ECHO,
	UNSET,
	EXPORT,
	EXIT,
	CD,
	NONE,
}			t_builtin;

/* Builtins */

void		ft_pwd(void);
void		ft_echo(char **arg);
//void		execute_builtin(t_builtin builtin, char *arg, bool option);
void	execute_builtin(t_builtin builtin, char **cmd);
void		error_builtin(t_builtin builtin);
t_builtin	is_builtin(char *buffer);

#endif
