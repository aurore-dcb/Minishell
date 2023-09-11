/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/11 10:53:08 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialise_pipex(pipex *pipex)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	// pipex->here_doc_file = -1;
	pipex->middle_cmd = NULL;
	pipex->middle_cmd_path = NULL;
}

int	parsing_pipex(pipex *pipex, s_data *data)
{
	pipex->paths = get_paths(&data->envp);
	if (!pipex->paths)
		return (ft_printf("ERROR -> Paths\n"), 0);
	if (!open_infile(pipex, data))
		return (ft_printf("ERROR -> Can't open infile\n"), 0);
	if (!open_outfile(pipex, data))
	{
		close(pipex->infile);
		return (ft_printf("ERROR -> Can't open outfile\n"), 0);
	}
	return (1);
}

int	ft_pipex(s_data *data)
{
	t_pid *pids;
	pipex pipex;

	pids = NULL;
	// 	return (ft_here_doc(argv, argc, env, &cmd));
	// else
	// {
	initialise_pipex(&pipex);
	if (!parsing_pipex(&pipex, data))
		return (1);
	data->cmd->in = pipex.infile;
	if (!loop_process(data, &pids, &pipex))
		return (printf("error loop process\n"), 1);
	wait_fct(&pids, &pipex, data);
	return (0);
}
