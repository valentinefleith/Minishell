/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:22 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/16 18:00:24 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_lexing(t_token *tokens)
 {
	 if (!tokens)
	 {
		 ft_printf("NULL\n");
		 return;
	 }
	 while (tokens)
	 {
		 if (tokens->next)
		 {
			 ft_printf("%s -> ", tokens->data);
			 tokens = tokens->next;
		 }
		 else {
			 ft_printf("%s\n", tokens->data);
			 break;
		 }
	 }
 }

void ft_print_token_types(t_token *tokens)
{
	if (!tokens)
	{
		ft_printf("NULL\n");
		return;
	}
	while (tokens)
	{
		ft_printf("%s\t\t:\t\t", tokens->data);
		if (tokens->type == 0)
			ft_printf("WORD");
		if (tokens->type == 1)
			ft_printf("INPUT");
		if (tokens->type == 2)
			ft_printf("HEREDOC");
		if (tokens->type == 3)
			ft_printf("OUTPUT");
		if (tokens->type == 4)
			ft_printf("APPEND");
		if (tokens->type == 5)
			ft_printf("PIPE");
		if (tokens->type == 6)
			ft_printf("FILENAME");
		if (tokens->type == 7)
			ft_printf("UNDEFINED");
		if (tokens->next)
		{
			ft_printf("\n ---------------------------- \n");
			 tokens = tokens->next;
		}
		else{
			ft_printf("\n");
			break;}
	}
}
