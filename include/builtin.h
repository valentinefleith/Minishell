/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/22 17:08:14 by luvallee         ###   ########.fr       */
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

void		ft_pwd(void);
void		ft_echo(char **arg);
void		execute_builtin(t_builtin builtin, char **cmd);
void		error_builtin(t_builtin builtin);
t_builtin	is_builtin(char *buffer);

int			ft_cd(t_env *env, char *path);
int			ft_env(t_env *env);
t_env		*ft_getenv(t_env *env, char *name);


#endif
