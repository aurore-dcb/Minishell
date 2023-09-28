/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:34:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:25:59 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_outfiles(t_cmd_line *cmd)
{
	int		fd;
	int		r_no;
	t_file	*new;
	t_token	*beg_token;

	r_no = 0;
	beg_token = cmd->token;
	while (beg_token)
	{
		if (beg_token->type == EXIT_FILE)
			fd = open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC, 0646);
		else if (beg_token->type == EXIT_FILE_RET)
			fd = open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND, 0646);
		if (beg_token->type == EXIT_FILE || beg_token->type == EXIT_FILE_RET)
		{
			r_no = errno;
			new = ft_lstnew_file(fd, r_no, beg_token->word);
			ft_lstadd_file(&cmd->outfile, new);
		}
		if (r_no != 0)
			return ;
		beg_token = beg_token->next;
	}
}
