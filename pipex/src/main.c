/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:49:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/03 15:00:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* Initialize every variables of the main struct/pipex */
void	ft_initialize(t_pipex *pipex)
{
	pipex->status = 0;
	pipex->nb_arg = 0;
	pipex->file_input = -1;
	pipex->file_output = -1;
	pipex->env = NULL;
	pipex->fd = NULL;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->env = NULL;
	pipex->child = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_initialize(&pipex);
	if (argc == 5)
	{
		pipex.env = envp;
		pipex.nb_arg = argc - 3;
		pipex.infile = argv[1];
		pipex.outfile = argv[pipex.nb_arg + 2];
		ft_parsing_cmd(&pipex, argv, 2, 2);
		ft_parsing_fd(&pipex);
		ft_pipex(&pipex, pipex.nb_arg);
		ft_close_files(&pipex, pipex.nb_arg);
		ft_free_everything(&pipex);
	}
	else
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		pipex.status = 1;
	}
	exit(pipex.status);
}
