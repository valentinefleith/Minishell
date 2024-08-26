/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/26 11:01:16 by vafleith         ###   ########.fr       */
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
typedef struct s_env_list t_env_list;
typedef struct s_btree t_btree;

/* Builtins */

t_builtin	is_builtin(char *buffer);
int			execute_builtin(t_builtin builtin, t_btree *tree, char **cmd, t_env_list *env);
int			ft_cd(t_env_list *env, char *path);
int			ft_env(t_env_list *env);
int			ft_pwd(t_env_list *env);
int			ft_echo(char **cmd);
int			ft_export(t_env_list *env, char *arg);
int			ft_unset(t_env_list *env, char **arg);
void		ft_exit(t_env_list *env, t_btree *tree, int	exit_status);
int			error_builtin(t_builtin builtin, char *arg);
t_env_list		*ft_getenv(t_env_list *env, char *name);


#endif
