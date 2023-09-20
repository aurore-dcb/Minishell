/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/20 15:02:49 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_lstadd_back_infile(t_infile **lst, t_infile *new)
{
	t_infile	*list;

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

t_infile	*ft_lstnew_infile(int fd, int err)
{
	t_infile	*elem;

	elem = malloc(sizeof(t_infile));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->fd = fd;
	elem->r_no = err;
	// elem->fd = open(fd, O_RDONLY);
	elem->r_no = errno;
	return (elem);
}

t_infile	*ft_lstlast_infile(t_infile *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	open_infile(s_data *data)
{
	cmd_line	*beg_cmd;
	token		*beg_token;
	t_infile	*new;

	beg_cmd = data->cmd;
	if (!beg_cmd)
		return (0);
	while (beg_cmd)
	{
		beg_token = beg_cmd->token;
		if (!beg_token)
			return (0);
		while (beg_token)
		{
			if (beg_token->type == 6)
			{
				new = ft_lstnew_infile(open(beg_token->word, O_RDONLY), errno);
				ft_lstadd_back_infile(&data->cmd->infile, new);
			}
			// if (beg_cmd->infile->r_no != 0)
				// return (1);
			beg_token = beg_token->next;
		}
		beg_cmd = beg_cmd->next;
	}
	return (1);
}

int	open_outfile(s_data *data)
{
	cmd_line	*cmd;
	token		*beg_token;

	cmd = data->cmd;
	if (!cmd)
		return (0);
	while (cmd)
	{
		beg_token = cmd->token;
		if (!beg_token)
			return (0);
		while (beg_token)
		{
			if (beg_token->type == EXIT_FILE)
				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC,
						0646);
			else if (beg_token->type == EXIT_FILE_RET)
				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND,
						0646);
			beg_token = beg_token->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
