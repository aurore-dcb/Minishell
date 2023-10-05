/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:26:31 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 10:39:10 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_here_doc(t_cmd_line *cmd)
{
	t_token	*tok;

	tok = cmd->token;
	if (tok)
	{
		while (tok)
		{
			if (tok->type == LIMITOR)
				return (1);
			tok = tok->next;
		}
	}
	return (0);
}

int	read_standart(t_pipex *pipex, char *to_find, t_data *data)
{
	char	*lign;
	t_token	*token_hd;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		lign = readline(">");
		if (g_flag == 130)
			return (unlink(".here_doc"), 1);
		if ((!lign || ft_strcmp(lign, to_find) == 0))
		{
			free(lign);
			return (1);
		}
		token_hd = NULL;
		if (!expand_here_doc(&token_hd, data, lign, pipex) || g_flag == 1)
			return (free_token(token_hd), 1);
		ft_putstr_fd("\n", pipex->here_doc_file);
		free_token(token_hd);
	}
	return (0);
}

int	standart_input(t_cmd_line *cmd, t_pipex *pipex, t_data *data)
{
	t_token	*tok;
	char	*to_find;

	to_find = "";
	tok = cmd->token;
	while (tok)
	{
		if (tok->type == LIMITOR)
		{
			g_flag = 0;
			to_find = tok->word;
			if (pipex->here_doc_file > 2)
				close(pipex->here_doc_file);
			unlink(".here_doc");
			pipex->here_doc_file = open(".here_doc",
					O_WRONLY | O_CREAT | O_TRUNC, 0646);
			if (pipex->here_doc_file == -1)
				return (0);
			if (!read_standart(pipex, to_find, data))
				return (0);
			if (g_flag == 130)
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}

int	proc_hd(t_pipex *pipex, t_cmd_line *cmd, t_data *data, t_pid **pids)
{
	if (!cmd->args[0])
		return (0);
	pipex->middle_cmd_path = find_path(pipex->paths, cmd->args[0]);
	if (!pipex->middle_cmd_path)
		return (0);
	if (builtins_no_pipe(cmd, data))
		return (1);
	if (!ft_process(pipex, pids, cmd, data))
		return (0);
	free(pipex->middle_cmd_path);
	return (1);
}

int	ft_hd(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids)
{
	if (!standart_input(cmd, pipex, data))
		return (0);
	if (g_flag == 1)
	{
		data->exit_status = 130;
		ft_lstadd_file(&cmd->infile, ft_lstnew_file(open("/dev/stdout",
					O_RDONLY), 0, ""));
	}
	else
	{
		data->exit_status = 0;
		ft_lstadd_file(&cmd->infile, ft_lstnew_file(pipex->here_doc_file, 0,
				""));
	}
	close(pipex->here_doc_file);
	pipex->here_doc_file = open(".here_doc", O_RDONLY);
	if (pipex->here_doc_file == -1)
		return (0);
	if (!proc_hd(pipex, cmd, data, pids))
		return (0);
	close(pipex->here_doc_file);
	unlink(".here_doc");
	return (1);
}
