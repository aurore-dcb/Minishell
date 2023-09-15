/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:26:31 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/14 14:37:11 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_here_doc(cmd_line *cmd)
{
	token	*tok;

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

int	parsing_here_doc(pipex *pipex)
{
	pipex->here_doc_file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC,
			0646);
	if (pipex->here_doc_file == -1)
		return (ft_printf("Error -> Can't create/open file\n"), 0);
	return (1);
}

void	standart_input(cmd_line *cmd, pipex *pipex)
{
	char	*lign;
	token	*tok;
	char	*to_find;

	lign = "ok";
	tok = cmd->token;
	while (tok)
	{
		if (tok->type == LIMITOR)
			to_find = tok->word;
		tok = tok->next;
	}
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		lign = get_next_line(0, to_find);
		if (!lign)
			break ;
		ft_putstr_fd(lign, pipex->here_doc_file);
		free(lign);
	}
}

int	process_here_doc(pipex *pipex, cmd_line *cmd, s_data *data, t_pid **pids)
{
	pipex->middle_cmd_path = find_path(pipex->paths, cmd->args[0]);
	if (!pipex->middle_cmd_path)
		return (0);
	if (builtins_no_pipe(cmd->args[0], data))
		return (1);
	if (!ft_process(pipex, pids, cmd, data))
		return (ft_printf("Error-> Process\n"), 0);
	free(pipex->middle_cmd_path);
	return (1);
}

int	ft_here_doc(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids)
{
	unlink(".here_doc");
	if (!parsing_here_doc(pipex))
		return (dprintf(1, "Error -> parse here_doc\n"), 0);
	standart_input(cmd, pipex);
	close(pipex->here_doc_file);
	pipex->here_doc_file = open(".here_doc", O_RDONLY);
	if (pipex->here_doc_file == -1)
		return (dprintf(1, "Error -> parse here_doc\n"), 0);
	cmd->in = pipex->here_doc_file;
	// si type arg :
	if (!process_here_doc(pipex, cmd, data, pids))
		return (0);
	close(pipex->here_doc_file);
	unlink(".here_doc");
	return (1);
}
