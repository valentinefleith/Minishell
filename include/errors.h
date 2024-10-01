/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:58:13 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/23 14:52:41 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

void	alloc_error(char *name);
t_token	*check_file_error(t_token *tokens, t_env *envs);

/* PARSING *******************************************************************/

t_token	*error_action(t_token *stack, t_token *tokens, t_token **output,
			int *state);

/* BUILTIN *******************************************************************/

/* BUILTIN *******************************************************************/

int		error_pwd(void);
int		error_cd(char *name);
int		error_export(char *name);
int		error_env(void);
int		error_exit(char *name);

/* EXECUTION *****************************************************************/

void	exit_child_process(t_shell *shell, int exit_status);
void	free_process(t_shell *shell);

/* PATHS *********************************************************************/

void	no_such_file(char *filename);
void	cmd_not_found(char *cmd_name);
void	permission_denied(char *name);
void	is_directory(char *name);

#endif
