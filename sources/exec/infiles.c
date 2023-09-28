/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:30:32 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_lstadd_file(t_file **lst, t_file *new)
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

t_file	*ft_lstnew_file(int fd, int err, char *file)
{
	t_file	*elem;

	elem = malloc(sizeof(t_file));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->fd = fd;
	elem->r_no = err;
	elem->name = ft_strdup(file);
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

void	add_infiles(t_cmd_line *cmd)
{
	int		fd;
	int		r_no;
	t_file	*new;
	t_token	*beg_token;

	r_no = 0;
	beg_token = cmd->token;
	while (beg_token)
	{
		if (beg_token->type == OPEN_FILE)
		{
			fd = open(beg_token->word, O_RDONLY);
			r_no = errno;
			new = ft_lstnew_file(fd, r_no, beg_token->word);
			ft_lstadd_file(&cmd->infile, new);
		}
		if (r_no != 0)
			return ;
		beg_token = beg_token->next;
	}
}

int	open_files(t_data *data)
{
	t_cmd_line	*beg_cmd;

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
	return (1);
}
