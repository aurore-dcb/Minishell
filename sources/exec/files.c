/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:29:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/13 14:04:47 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// int	open_infile(pipex *pipex, s_data *data)
// {
// 	(void)pipex;
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
// 			if (beg_token->type == 6)
// 				open(beg_token->word, O_RDONLY);
// 			beg_token = beg_token->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (1);
// }

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

int	open_outfile(pipex *pipex, s_data *data)
{
	(void)pipex;
	cmd_line *cmd;
	token *beg_token;
	
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
				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_TRUNC, 0646);
			else if (beg_token->type == EXIT_FILE_RET)
				cmd->out = open(beg_token->word, O_WRONLY | O_CREAT | O_APPEND, 0646);
			beg_token = beg_token->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
