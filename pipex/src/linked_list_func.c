/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:22:31 by luvallee          #+#    #+#             */
/*   Updated: 2024/05/30 17:14:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	if (*lst == NULL)
	{
		new->next = NULL;
		*lst = new;
		return ;
	}
	else
	{
		new->next = NULL;
		last = ft_last_node(*lst);
		last->next = new;
	}
}
