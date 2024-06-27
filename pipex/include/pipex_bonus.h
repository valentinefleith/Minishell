/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:42:14 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/04 13:43:59 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../bonus/get_next_line/get_next_line.h"
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
# define TRUE 42

typedef enum e_file
{
	infile,
	outfile,
	here_doc,
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

typedef struct s_here_doc
{
	int				here;
	char			*limiter;
}					t_here_doc;

typedef struct s_pipex
{
	int				status;
	int				nb_arg;
	int				nb_cmd;
	int				file_input;
	int				file_output;
	int				**fd;
	char			*infile;
	char			*outfile;
	char			**env;
	t_child			*child;
	t_here_doc		here_doc;
}					t_pipex;

int					main(int argc, char **argv, char **envp);
void				ft_initialize(t_pipex *pipex);
/* Parsing */
void				ft_parsing(t_pipex *pipex, char **argv, int fd);
void				ft_parsing_here_doc(char *lim, int fd, char *input);
void				ft_parsing_cmd(t_pipex *pipex, char **argv, int j, int i);
char				**ft_parsing_path(char **env);
void				ft_parsing_fd(t_pipex *pipex);
/* Checking access */
int					ft_checking_file_access(t_pipex *pipex, t_file file);
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
void				ft_count_arg(t_pipex *pipex, int argc);
void				ft_creating_pipe(t_pipex *pipex, int count);
void				ft_free_everything(t_pipex *pipex);
char				**ft_handle_cmd_diff(t_child **new, char **argv, int index);
void				ft_print_error(t_pipex *pipex, t_child *child, int signal);
/* Clean up */
void				ft_closing_files(t_pipex *pipex, int count);
void				ft_closing_arg(t_pipex *pipex);
void				ft_deleting_fd(int **fd, int count);
void				ft_deleting_list(t_child **child);
void				ft_deleting_tab(char **tab);
/* Linked list */
void				ft_add_back(t_child **lst, t_child *new);
t_child				*ft_last_node(t_child *lst);

#endif