/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 11:14:51 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_infile(pipex *pipex, s_data *data)
{
	char		*file;
	cmd_line	*beg_cmd;
	token		*beg_token;

	file = NULL;
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
	if (!file)
		pipex->infile = open("/dev/stdin", O_RDONLY);
	else
	{
		pipex->infile = open(file, O_RDONLY);
		if (pipex->infile == -1)
			return (0);
	}
	return (1);
}

int	ft_lstadd_back_files(t_outfile **lst, t_outfile *new)
{
	t_outfile	*list;

	if (!new)
		return (0);
	list = *lst;
	printf("new = %d\n", new->outfile);
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*lst = new;
	return (1);
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
				new = ft_lstnew_files(open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC, 0646));
			else if (beg_token->type == 9)
				new = ft_lstnew_files(open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND, 0646));
			if (beg_token->type == 8 || beg_token->type == 9)
				ft_lstadd_back_files(&pipex->outfiles, new);
			// if (!ft_lstadd_back_files(&pipex->outfiles, new))
			// 	return (0);
			beg_token = beg_token->next;
		}
		beg_cmd = beg_cmd->next;
	}
	return (1);
}
