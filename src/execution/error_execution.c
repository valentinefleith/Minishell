/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:16:13 by luvallee          #+#    #+#             */
/*   Updated: 2024/08/28 17:29:18 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_execution(t_shell *shell, t_btree *tree, int exit_code)
{
	close_fd(shell);
	free_process(shell, tree);
	exit(exit_code);
}
