/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/07/15 17:17:56 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void ft_print_lexing(t_token *tokens)
// {
// 	if (!tokens)
// 	{
// 		ft_printf("NULL\n");
// 		return;
// 	}
// 	while (tokens)
// 	{
// 		if (tokens->next)
// 		{
// 			ft_printf("%s -> ", tokens->data);
// 			tokens = tokens->next;
// 		}
// 		else {
// 			ft_printf("%s\n", tokens->data);
// 			break;
// 		}
// 	}
// }

static void ft_print_token_types(t_token *tokens)
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

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	//t_cmd	cmd;
	t_token **tokens;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		// ft_printf("$> ");
		// buffer = get_next_line(0);
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		tokens = tokenize_cmdline(buffer);
		// ft_print_lexing(*tokens);
		ft_print_token_types(*tokens);
		parsing_grammar_rules(tokens);
		//cmd = parse_user_prompt(buffer, env);
		// execute_command(cmd, env);
		// ft_printf("%s\n", buffer);
		// rl_on_new_line();
		free(buffer);
	}
	// rl_clear_history();
}
