/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:22 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/22 15:28:03 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_lexing(t_token *tokens)
{
	if (!tokens)
	{
		ft_printf("NULL\n");
		return ;
	}
	while (tokens)
	{
		if (tokens->next)
		{
			ft_printf("%s -> ", tokens->data);
			tokens = tokens->next;
		}
		else
		{
			ft_printf("%s\n", tokens->data);
			break ;
		}
	}
}

void	print_single_token_type(t_token_type type)
{
	if (type == 0)
		printf("WORD\n");
	if (type == 1)
		printf("INPUT\n");
	if (type == 2)
		printf("HEREDOC\n");
	if (type == 3)
		printf("OUTPUT\n");
	if (type == 4)
		printf("APPEND\n");
	if (type == 5)
		printf("PIPE\n");
	if (type == 6)
		printf("FILENAME\n");
	if (type == 7)
		printf("UNDEFINED\n");
	if (type == 8)
		printf("CMD\n");
}

void	ft_print_token_types(t_token *tokens)
{
	if (!tokens)
	{
		ft_printf("NULL\n");
		return ;
	}
	while (tokens)
	{
		ft_printf("%s\t\t:\t\t", tokens->data);
		print_single_token_type(tokens->type);
		if (tokens->next)
		{
			ft_printf("\n ---------------------------- \n");
			tokens = tokens->next;
		}
		else
		{
			ft_printf("\n");
			break ;
		}
	}
}
