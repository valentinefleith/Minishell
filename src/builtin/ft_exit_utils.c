/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:23 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/27 14:24:55 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nb_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

bool	nb_overflows(unsigned long long nb, bool is_negative)
{
	unsigned long long	limit;

	limit = 9223372036854775807;
	return ((!is_negative && nb > limit) || (is_negative && nb > limit + 1));
}

int	get_last_exit_status(t_env_list *env_list)
{
	t_env_list	*code;

	code = ft_getenv(env_list, "?");
	if (!code)
		return (0);
	return (ft_atoi(code->data));
}
