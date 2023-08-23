/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/23 16:26:22 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

void	ft_lstadd_back_cmd_line(cmd_line **lst, cmd_line *new)
{
	cmd_line	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*lst = new;
}

cmd_line	*ft_lstnew_cmd_line(int len)
{
	cmd_line	*elem;

	elem = malloc(sizeof(cmd_line));
	if (!elem)
		return (NULL);
	elem->cmd = malloc(sizeof(char) * len);
	if (!elem->cmd)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

cmd_line	*ft_lstlast_cmd_line(cmd_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
