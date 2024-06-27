/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:02:52 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/03 14:14:47 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERROR -1

typedef enum e_file
{
	infile,
	outfile,
}					t_file;

typedef struct s_child
{
	int				index;
	int				pid;
	int				executable;
	char			**cmd;
	char			**path;
	char			*cmd_path;
	struct s_child	*next;
}					t_child;

typedef struct s_pipex
{
	int				status;
	int				nb_arg;
	int				file_input;
	int				file_output;
	int				**fd;
	char			*infile;
	char			*outfile;
	char			**env;
	t_child			*child;
}					t_pipex;

int					main(int argc, char **argv, char **envp);
void				ft_initialize(t_pipex *pipex);

/* Parsing */

void				ft_parsing_cmd(t_pipex *pipex, char **argv, int j, int i);
char				**ft_parsing_path(char **env);
void				ft_parsing_fd(t_pipex *pipex);
void				ft_creating_pipe(t_pipex *pipex, int count);
char				**ft_handle_diff(t_child **new, char **argv, int index);

/* Checking access */

int					ft_checking_files_access(t_pipex *pipex, t_file file);
int					ft_checking_cmd_access(t_pipex *pipex, char *path);
void				ft_opening_file(t_pipex *pipex, t_file file);
void				ft_execute_option(t_child *child);
void				ft_execute_executable(t_pipex *pipex, t_child *child,
						int signal);

/* Pipex process */

void				ft_pipex(t_pipex *pipex, int count);
void				ft_child_process(t_pipex *pipex, t_child *child, int index);
void				ft_duplicate_fd(t_pipex *pipex, int index);
void				ft_executing(t_pipex *pipex, t_child *child, char **env);
void				ft_waiting(t_pipex *pipex, int count, int status);

/* Utils */
void				ft_free_everything(t_pipex *pipex);
void				ft_print_error(t_pipex *pipex, t_child *child, int error);

/* Clean up */

void				ft_deleting_list(t_child **child);
void				ft_deleting_fd(int **fd, int count);
void				ft_deleting_tab(char **tab);
void				ft_close_arg(t_pipex *pipex);
void				ft_close_files(t_pipex *pipex, int count);

/* Linked list */
void				ft_add_back(t_child **lst, t_child *new);
t_child				*ft_last_node(t_child *lst);

#endif