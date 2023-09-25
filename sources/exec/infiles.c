/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/25 14:33:34 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	display_file(s_data *data)
{
	cmd_line	*cmd;
	t_file		*out;

	dprintf(1, "DISPLAY\n");
	cmd = data->cmd;
	while (cmd)
	{
		out = cmd->infile;
		while (out)
		{
			dprintf(1, "fd = %d    r_no = %d\n", out->fd, out->r_no);
			out = out->next;
		}
		cmd = cmd->next;
	}
}

void	ft_lstadd_back_file(t_file **lst, t_file *new)
{
	t_file	*list;

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

t_file	*ft_lstnew_file(int fd, int err)
{
	t_file	*elem;

	elem = malloc(sizeof(t_file));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->fd = fd;
	elem->r_no = err;
	elem->r_no = errno;
	return (elem);
}

t_file	*ft_lstlast_file(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_infiles(cmd_line *cmd)
{
	int		fd;
	int		r_no;
	t_file	*new;
	token	*beg_token;

	r_no = 0;
	beg_token = cmd->token;
	while (beg_token)
	{
		if (beg_token->type == OPEN_FILE)
		{
			fd = open(beg_token->word, O_RDONLY);
			r_no = errno;
			new = ft_lstnew_file(fd, r_no);
			ft_lstadd_back_file(&cmd->infile, new);
		}
		if (r_no != 0)
			return ;
		beg_token = beg_token->next;
	}
}

int	open_files(s_data *data)
{
	cmd_line	*beg_cmd;

	beg_cmd = data->cmd;
	if (!beg_cmd)
		return (0);
	while (beg_cmd)
	{
		if (!beg_cmd->token)
			return (0);
		add_infiles(beg_cmd);
		add_outfiles(beg_cmd);
		beg_cmd = beg_cmd->next;
	}
	// display_file(data);
	return (1);
}
