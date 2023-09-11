/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:32:34 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/11 15:22:43 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_pid	*ft_lstnew_pipex(pid_t pid)
{
	t_pid	*elem;

	elem = malloc(sizeof(t_pid));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->pid = pid;
	return (elem);
}

int	ft_lstadd_back_pipex(t_pid **lst, t_pid *new)
{
	t_pid	*list;

	// if (lst)
	// {
	list = *lst;
	if (!new)
		return (0);
	if (list && new)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
	{
		*lst = new;
	}
	return (1);
	// }
}
