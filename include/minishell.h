/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/26 17:07:43 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "env.h"
# include "execution.h"
# include "free.h"
# include "get_next_line.h"
# include "libft.h"
# include "parsing.h"
# include "errors.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_signal;

#define SUCCESS 0
#define MALLOC_ERROR 1

typedef enum e_builtin	t_builtin;

typedef struct s_env_list
{
	char				*name;
	char				*data;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_env
{
	t_env_list			*env_list;
	char				**env_tab;
}						t_env;

typedef struct s_shell
{
	int					nb_cmd;
	int					pid;
	int					prev_read;
	int					read;
	int					write;
	char				**paths;
	struct s_env		*envs;
	t_btree *main_root;
}						t_shell;

// void	signal_monitor_interactive(t_env_list *env_list);
// void					signal_handler_interactive(int signal);
// void					signal_monitor_unteractive(void);
// void	signal_monitor(bool child);
void	signal_monitor(bool child_process, bool interaction_mode);

#endif
