/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/27 14:20:20 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"
# include "parsing.h"
# include <stdbool.h>

# define STR_I64_MAX "9223372036854775807"
# define STR_I64_MIN "-9223372036854775808"

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
}						t_builtin;

typedef struct s_btree	t_btree;
typedef struct s_shell	t_shell;

/* Builtins */

t_builtin				is_builtin(char *buffer);
int						execute_builtin(t_builtin builtin, t_btree *tree,
							bool pipeline, t_shell *shell);
void					builtin_redirection(t_btree *tree, t_shell *shell);

int						ft_cd(t_env *env, char **cmd);
int						ft_env(t_env_list *env, int fd, bool option);
int						ft_pwd(t_env *env, int fd);
int						ft_echo(char **cmd, int fd);
int						ft_export(t_env *env, char **arg, int fd);
int						ft_exit(t_shell *shell, char **cmd, t_btree *tree);
int						ft_unset(t_env *env, char **arg);

bool					is_arg_unique(char **cmd);
t_env_list				*ft_getenv_boost(t_env_list *env, char *name, int len);
size_t					find_len_name(char *arg);
int						export_malloc_error(void);
char					*ft_strcat(char *dest, char *src);

int						error_builtin(t_builtin builtin, char *arg);
void					free_builtin_process(t_shell *shell, int *exit_code);
t_env_list				*ft_getenv(t_env_list *env, char *name);

#endif
