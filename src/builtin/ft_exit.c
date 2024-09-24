/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/24 11:32:33 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atol(char *str)
{
	long	output;
	int		is_neg;

	if (!*str)
		return (0);
	while (*str && ft_strchr(" \t\n\r\v\f", *str))
		str++;
	is_neg = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = 1;
		str++;
	}
	output = 0;
	while (ft_isdigit(*str))
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	if (is_neg)
		return (-output);
	return (output);
}

static int	count_nb_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static int	exit_error(char *name)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (2);
}

static int	get_last_exit_status(t_env_list *env_list)
{
	t_env_list	*code;

	code = ft_getenv(env_list, "?");
	if (!code)
		return (0);
	return (ft_atoi(code->data));
}

static bool	is_valid_nb(char *arg)
{
	int	len;

	while (*arg && ft_strchr(" \t\n\r\v\f", *arg))
		arg++;
	if (!arg)
		return (false);
	while (*arg == '0')
		arg++;
	if (!arg)
		return (true);
	len = 0;
	while (*arg && (ft_isdigit(*arg) || *arg == '-' || *arg == '+'))
	{
		if ((*arg == '-' || *arg == '+') && len != 0)
			return (false);
		len++;
		arg++;
	}
	while (*arg && ft_strchr(" \t\n\r\v\f", *arg))
		arg++;
	if (*arg || len > 12)
		return (false);
	return (true);
}

static int	parse_exit_status(t_env_list *env_list, char **cmd)
{
	int		nb_args;
	long	code;

	nb_args = count_nb_args(cmd);
	if (nb_args == 1)
		return (get_last_exit_status(env_list));
	if (!is_valid_nb(cmd[1]))
		return (exit_error(cmd[1]));
	code = ft_atol(cmd[1]);
	if (code > INT_MAX || code < INT_MIN)
		return (exit_error(cmd[1]));
	if (nb_args > 2)
	{
		ft_putendl_fd("bash: too many arguments", 2);
		return (-1);
	}
	if (code < 0)
		return (code + (- code / 256 + 1) * 256);
	return (code % 256);
}

int	ft_exit(t_shell *shell, t_btree *tree, char **cmd)
{
	int	exit_status;

	exit_status = parse_exit_status(shell->envs->env_list, cmd);
	if (exit_status < 0)
		return 1;
	printf("exit\n");
	if (shell->envs->env_list)
		shell->envs->env_list = free_env_list(shell->envs->env_list);
	if (shell->envs->env_tab)
	{
		ft_free_tab(shell->envs->env_tab);
		shell->envs->env_tab = NULL;
	}
	if (shell->envs)
	{
		free(shell->envs);
		shell->envs = NULL;
	}
	if (tree)
	{
		btree_free(tree);
		tree = NULL;
	}
	ft_free_tab(shell->paths);
	exit(exit_status);
}
