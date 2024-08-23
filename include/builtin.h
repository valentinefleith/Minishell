/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/23 15:54:58 by luvallee         ###   ########.fr       */
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
typedef struct s_btree t_btree;

/* Builtins */

t_builtin	is_builtin(char *buffer);
int			execute_builtin(t_builtin builtin, t_btree *tree, char **cmd, t_env *env);
int			ft_cd(t_env *env, char *path);
int			ft_env(t_env *env);
int			ft_pwd(t_env *env);
int			ft_echo(char **cmd);
int			ft_export(t_env *env, char *arg);
int			ft_unset(t_env *env, char **arg);
void		ft_exit(t_env *env, t_btree *tree, int	exit_status);
int			error_builtin(t_builtin builtin, char *arg);
t_env		*ft_getenv(t_env *env, char *name);


#endif
