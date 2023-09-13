/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:40:24 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/13 09:32:21 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	nb_arg(cmd_line *list)
{
	token	*cur;
	int		len;

	len = 0;
	cur = list->token;
	while (cur)
	{
		if (cur->type == ARG)
			len++;
		cur = cur->next;
	}
	return (len);
}

void	fill_arg(cmd_line *list)
{
	token	*cur;
	int		i;

	cur = list->token;
	i = 0;
	while (cur)
	{
		if (cur->type == ARG)
		{
			list->args[i] = ft_substr(cur->word, 0, ft_strlen(cur->word));
			i++;
		}
		cur = cur->next;
	}
	list->args[i] = NULL;
}

int	tab_cmd(cmd_line **list)
{
	cmd_line *begin;
	char **cmd;

	begin = *list;
	while (begin)
	{
		cmd = malloc(sizeof(char *) * (nb_arg(begin) + 1));
		if (!cmd)
			return (0);
		begin->args = cmd;
		fill_arg(begin);
		begin = begin->next;
	}
	return (1);
}