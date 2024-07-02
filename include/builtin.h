/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2024/07/02 15:58:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum e_builtin
{
	PWD, 
	ECHO,
	ECHO_N,
	UNSET,
	EXPORT,
	EXIT,
	CD,
	NONE,
}			t_builtin;

typedef struct s_input t_input;

void		parse_builtin(char **buffer, t_input *input);
void		execute_builtin(t_builtin builtin, t_input *input);
void		ft_pwd(void);
void		error_builtin(t_builtin builtin);

#endif