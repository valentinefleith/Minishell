/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:35:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/09/27 14:19:20 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//static unsigned long long ft_unsigned(char *str)
//{
//	unsigned long long output;
//
//	output = 0;
//	while (ft_isdigit(*str))
//	{
//		output = output * 10 + (*str - '0');
//		str++;
//	}
//	return output;
//}

static unsigned long long ft_atoul(char *str, bool *is_negative)
{
	unsigned long long output;

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
	return output;
}

static int	count_nb_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
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

static bool nb_overflows(unsigned long long nb, bool is_negative)
{
	unsigned long long limit;

	limit = 9223372036854775807;
	return (!is_negative && nb > limit) || (is_negative && nb > limit + 1);
}

static int	parse_exit_status(t_env_list *env_list, char **cmd)
{
	int		nb_args;
	unsigned long long	code;
	bool is_negative;

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
		return (- code + (code / 256 + 1) * 256);
	return (code % 256);
}

int	ft_exit(t_shell *shell, char **cmd, t_btree *tree)
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
		btree_free(tree);
	ft_free_tab(shell->paths);
	exit(exit_status);
}
