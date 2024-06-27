/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:29 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/03 16:26:55 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/* Search last node of the linked list */
t_child	*ft_last_node(t_child *lst)
{
	t_child	*temp;

	temp = NULL;
	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

/* Add node at the end of the linked list */
void	ft_add_back(t_child **lst, t_child *new)
{
	t_child	*last;

	if (!new)
		return ;
	last = NULL;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_last_node(*lst);
		last->next = new;
	}
}
