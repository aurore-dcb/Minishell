/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:27:11 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_lstadd_back_cmd_line(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*list;

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

t_cmd_line	*ft_lstnew_cmd_line(int len)
{
	t_cmd_line	*elem;

	elem = malloc(sizeof(t_cmd_line));
	if (!elem)
		return (NULL);
	elem->cmd = malloc(sizeof(char) * len);
	if (!elem->cmd)
		return (NULL);
	ft_bzero(elem->cmd, len);
	elem->infile = NULL;
	elem->outfile = NULL;
	elem->fd[0] = 0;
	elem->fd[1] = 0;
	elem->token = NULL;
	elem->next = NULL;
	elem->args = NULL;
	return (elem);
}

t_cmd_line	*ft_lstlast_cmd_line(t_cmd_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ft_lstnew_token(t_cmd_line *list, int start, int end)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!elem->word)
		return (NULL);
	ft_strcpy_pos(elem->word, list->cmd, start, end);
	elem->type = get_type_meta(elem->word);
	elem->next = NULL;
	elem->previous = NULL;
	return (elem);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
		list->next->previous = list;
	}
	else
		*lst = new;
}
