//  cat Makefile | grep minishell
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/08/28 14:43:19 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "parsing.h"
# include "free.h"
# include "execution.h"
# include "builtin.h"
# include "env.h"


# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct s_env_list
{
	char			*name;
	char			*data;
	struct s_env_list	*next;
}					t_env_list;

typedef struct s_env
{
	t_env_list *env_list;
	char **env_tab;
}				t_env;

typedef struct s_shell
{
	int				nb_cmd;
	int				pid;
	int				read;
	int				write;
	char			**paths;
	struct s_env	*envs;
}					t_shell;

// typedef struct s_shell
// {
// 	int				pid;
// 	int				fd_in;
// 	int				fd_out;
// 	int				nb_cmd;
// 	int				**pipe_fd;
// 	char			**paths;
// 	struct s_env	*envs;
// }					t_shell;

#endif
