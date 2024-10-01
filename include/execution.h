/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:19 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/01 15:33:17 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "minishell.h"
# include "parsing.h"

typedef struct s_shell	t_shell;

/********************** Pipeline *********************************************/

int						launch_pipeline(t_btree *root, t_env *envs,
							char **paths);
void					duplicate_fd(t_shell *shell);
int						close_fd(int *fd);
int						waiting(t_shell *shell, int last_pid);

/********************** Execution ********************************************/

int						execute_ast(t_btree *root, t_shell *shell);
void					child_process(t_btree *tree, t_shell *shell);
int						cmd_execution(t_shell *shell, t_btree *tree);

/********************** Redirection ******************************************/

int						file_redirection(t_btree *tree, t_shell *shell, int fd,
							int type);
char					*find_redirection(t_btree *tree, t_shell *shell,
							char *filename, int target);
int						which_redirection_type(char *operator);
int						open_file(char *filename, int file_type);
int						last_redirection(t_btree *tree, int *type, char *name);

/********************** Path *************************************************/

char					**get_paths(t_env_list *env_list);
char					*get_path_env(char *cmd_name, char **paths);
char					*get_full_cmd_path(char *command_name, char **paths);
char					*get_path_no_env(char *cmd_name);

/********************* Signals ***********************************************/

void					signal_monitor(bool child_process,
							bool interaction_mode);

/********************* Utils *************************************************/

int						count_cmd(t_btree *tree, int *nb_cmd);
int						check_file_access(char *filename, int file_type);
int						checking_cmd_access(char *cmd_name, char *path);

#endif
