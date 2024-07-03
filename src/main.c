/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/03 12:04:25 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_print_lexing(t_token *tokens)
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

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	//t_cmd	cmd;
	t_token **tokens;

	(void)argc;
	(void)argv;
	while (1)
	{
		// ft_printf("$> ");
		// buffer = get_next_line(0);
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		tokens = tokenize_cmdline(buffer);
		ft_print_lexing(*tokens);
		//cmd = parse_user_prompt(buffer, env);
		// execute_command(cmd, env);
		// ft_printf("%s\n", buffer);
		// rl_on_new_line();
		free(buffer);
	}
	// rl_clear_history();
}
