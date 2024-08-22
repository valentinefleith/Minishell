/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/22 18:41:27 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parsing.h"
# include <stdbool.h>

typedef enum e_builtin
{
	PWD, 
	ECHO,
	UNSET,
	EXPORT,
	EXIT,
	CD,
	ENV,
	NONE,
}			t_builtin;

typedef struct s_env t_env;

/* Builtins */

void		execute_builtin(t_builtin builtin, char **cmd, t_env *env);
void		error_builtin(t_builtin builtin);
t_builtin	is_builtin(char *buffer);

int			ft_cd(t_env *env, char *path);
int			ft_env(t_env *env);
int			ft_pwd(t_env *env);
int			ft_echo(char **cmd);
t_env		*ft_getenv(t_env *env, char *name);


#endif
