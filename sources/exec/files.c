/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 12:34:06 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_infile(pipex *pipex, s_data *data)
{
	char		*file;
	cmd_line	*beg_cmd;
	token		*beg_token;

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
				file = beg_token->word;
			beg_token = beg_token->next;
		}
		beg_cmd = beg_cmd->next;
	}
	pipex->infile = open(file, O_RDONLY);
	if (pipex->infile == -1)
		return (0);
	return (1);
}

void	ft_lstadd_back_files(t_outfile **lst, t_outfile *new)
{
	t_outfile	*list;

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

t_outfile	*ft_lstnew_files(int fd)
{
	t_outfile	*elem;

	elem = malloc(sizeof(t_outfile));
	if (!elem)
		return (NULL);
	elem->outfile = fd;
	elem->next = NULL;
	return (elem);
}

int open_outfile(pipex *pipex, s_data *data)
{
	cmd_line *beg_cmd;
	token	*beg_token;
	t_outfile *new;

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
			if (beg_token->type == 8)
			{
				new = ft_lstnew_files(open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC, 0646));
			}
			else if (beg_token->type == 9)
			{
				new = ft_lstnew_files(open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND, 0646));
			}
			ft_lstadd_back_files(&pipex->outfiles, new);
			beg_token = beg_token->next;
		}
		beg_cmd = beg_cmd->next;
	}
	return (1);
}