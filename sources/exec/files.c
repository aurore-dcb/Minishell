/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/15 15:28:29 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_infile(s_data *data)
{
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
			{
				beg_cmd->in = open(beg_token->word, O_RDONLY);
				beg_cmd->error = errno;
			}
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
