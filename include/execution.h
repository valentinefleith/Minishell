/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:19 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/26 13:54:11 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "minishell.h"
# include "parsing.h"

typedef struct s_shell	t_shell;

void					execute_pipeline_bis(t_btree *root, t_env *env,
							char **paths);

int						launch_pipeline(t_btree *tree, t_env *envs,
							char **paths);
int						execute_ast(t_btree *root, t_shell *shell);
void					child_process(t_btree *tree, t_shell *shell);
int						cmd_execution(t_shell *shell, t_btree *tree);
int						waiting(t_shell *shell, int last_pid);
int						close_fd(int *fd);

int						file_redirection(t_btree *tree, t_shell *shell, int fd,
							int type);
char					*find_input(t_btree *tree, t_shell *shell, char *name);
char					*find_output(t_btree *tree, t_shell *shell, char *name);

int						open_file(char *filename, int file_type);
int						check_file_access(char *filename, int file_type);
int						checking_cmd_access(char *cmd_name, char *path);
char					*parsing_heredoc(char *limit, int len);

int						count_cmd(t_btree *tree, int *nb_cmd);
char					*get_path_env(char *cmd_name, char **paths);
char					*get_full_cmd_path(char *command_name, char **paths);
char					*get_path_no_env(char *cmd_name);

void					error_execution(t_shell *shell, int exit_code);
void					debug_exec(t_btree *tree, t_shell *shell, int index);

void					no_such_file(char *filename);
void					cmd_not_found(char *cmd_name);
void					permission_denied(char *name);
void					is_directory(char *name);

#endif
