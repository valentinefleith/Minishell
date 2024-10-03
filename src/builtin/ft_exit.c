/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/10/03 15:01:25 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	ft_atoul(char *str, bool *is_negative)
{
	unsigned long long	output;

	if (!*str)
		return (0);
	while (*str && ft_strchr(" \t\n\r\v\f", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*is_negative = true;
		str++;
	}
	output = 0;
	while (ft_isdigit(*str))
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output);
}

static bool	is_valid_nb(char *arg)
{
	size_t	len;

	while (*arg && ft_strchr(" \t\n\r\v\f", *arg))
		arg++;
	if (!arg)
		return (false);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg && *arg == '0')
		arg++;
	len = 0;
	while (*arg && ft_isdigit(*arg))
	{
		len++;
		arg++;
	}
	while (*arg && ft_strchr(" \t\n\r\v\f", *arg))
		arg++;
	if (*arg || len > ft_strlen(STR_I64_MAX))
		return (false);
	return (true);
}

static int	parse_exit_status(t_env_list *env_list, char **cmd)
{
	int					nb_args;
	unsigned long long	code;
	bool				is_negative;

	nb_args = count_nb_args(cmd);
	if (nb_args == 1)
		return (get_last_exit_status(env_list));
	if (!is_valid_nb(cmd[1]))
		return (error_exit(cmd[1]));
	is_negative = false;
	code = ft_atoul(cmd[1], &is_negative);
	if (nb_overflows(code, is_negative))
		return (error_exit(cmd[1]));
	if (nb_args > 2)
	{
		ft_putendl_fd("bash: too many arguments", 2);
		return (-1);
	}
	if (is_negative)
		return (-code + (code / 256 + 1) * 256);
	return (code % 256);
}

int	ft_exit(t_shell *shell, char **cmd, int fd)
{
	int	exit_status;

	exit_status = parse_exit_status(shell->envs->env_list, cmd);
	if (exit_status < 0)
		return (1);
	ft_putendl_fd("exit", fd);
	if (shell->envs)
		shell->envs = free_envs(shell->envs);
	if (shell->main_root)
	{
		btree_free(shell->main_root);
		shell->main_root = NULL;
	}
	close_fd(&shell->prev_read);
	close_fd(&shell->read);
	close_fd(&shell->write);
	ft_free_tab(shell->paths);
	exit(exit_status);
}
