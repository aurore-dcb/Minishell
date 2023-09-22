/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:34:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 15:51:41 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void	ft_lstadd_back_file(t_file **lst, t_file *new)
// {
// 	t_file	*list;

// 	list = *lst;
// 	if (list)
// 	{
// 		while (list->next)
// 			list = list->next;
// 		list->next = new;
// 	}
// 	else
// 		*lst = new;
// }

// t_file	*ft_lstnew_file(int fd, int err)
// {
// 	t_file	*elem;

// 	elem = malloc(sizeof(t_file));
// 	if (!elem)
// 		return (NULL);
// 	elem->next = NULL;
// 	elem->fd = fd;
// 	elem->r_no = err;
// 	elem->r_no = errno;
// 	return (elem);
// }

// t_file	*ft_lstlast_file(t_file *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

void	add_outfiles(cmd_line *cmd)
{
	int		fd;
	int		r_no;
	t_file	*new;
	token	*beg_token;

    r_no = 0;
	beg_token = cmd->token;
	while (beg_token)
	{
		if (beg_token->type == EXIT_FILE)
			fd = open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC, 0646);
        else if (beg_token->type == EXIT_FILE_RET)
            fd = open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND, 0646);
        r_no = errno;
        new = ft_lstnew_file(fd, r_no);
		ft_lstadd_back_file(&cmd->infile, new);
		if (r_no != 0)
			return ;
		beg_token = beg_token->next;
	}
}

// int	open_outfile(s_data *data)
// {
// 	cmd_line *cmd;
// 	token *beg_token;

// 	cmd = data->cmd;
// 	if (!cmd)
// 		return (0);
// 	while (cmd)
// 	{
// 		beg_token = cmd->token;
// 		if (!beg_token)
// 			return (0);
// 		while (beg_token)
// 		{
// 			if (beg_token->type == EXIT_FILE)
// 				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC,
// 						0646);
// 			else if (beg_token->type == EXIT_FILE_RET)
// 				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND,
// 						0646);
// 			beg_token = beg_token->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (1);
// }