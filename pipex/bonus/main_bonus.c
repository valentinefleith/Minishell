/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:01:04 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/04 13:46:35 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/* Initialize every variables of pipex's struct */
void	ft_initialize(t_pipex *pipex)
{
	pipex->status = 0;
	pipex->nb_arg = 0;
	pipex->nb_cmd = 0;
	pipex->file_input = -1;
	pipex->file_output = -1;
	pipex->fd = NULL;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->env = NULL;
	pipex->child = NULL;
	pipex->here_doc.here = -1;
	pipex->here_doc.limiter = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_initialize(&pipex);
	if (argc >= 5)
	{
		if (ft_strnstr(argv[1], "here_doc", 8) != NULL)
			pipex.here_doc.here = TRUE;
		ft_count_arg(&pipex, argc);
		pipex.env = envp;
		pipex.infile = argv[1];
		pipex.outfile = argv[pipex.nb_arg];
		ft_parsing(&pipex, argv, -1);
		ft_pipex(&pipex, pipex.nb_cmd);
		ft_closing_files(&pipex, pipex.nb_cmd);
		ft_free_everything(&pipex);
	}
	exit(pipex.status);
}
