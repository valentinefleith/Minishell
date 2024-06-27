/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:08 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/31 12:46:29 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* Call every functions necessary to clean up all the program */
void	ft_free_everything(t_pipex *pipex)
{
	ft_deleting_list(&pipex->child);
	ft_deleting_fd(pipex->fd, pipex->nb_arg);
}

void	ft_print_error(t_pipex *pipex, t_child *child, int error)
{
	if (error == 127 && child->cmd_path != NULL && pipex->env != NULL)
	{
		ft_putstr_fd("/usr/bin/", 2);
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error == 127 || child->cmd[0] == NULL)
	{
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (error == 126)
	{
		ft_putstr_fd(child->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}
