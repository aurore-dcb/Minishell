/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 15:57:29 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialise_pipex(pipex *pipex)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	pipex->outfiles = NULL;
	// pipex->here_doc_file = -1;
	pipex->middle_cmd = NULL;
	pipex->middle_cmd_path = NULL;
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
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
	// t_parsing	data;
	// t_cmd		*cmd;

	pids = NULL;
	// pipex = NULL;
	// cmd = NULL;
	// if (is_here_doc(argc, argv))
	// 	return (ft_here_doc(argv, argc, env, &cmd));
	// else
	// {
	data->cmd->in = pipex.infile;
	initialise_pipex(&pipex);
	if (!parsing_pipex(&pipex, data))
		return (1);
	if (!loop_process(data, &pids, &pipex))
		printf("error loop process\n");
		// return (error_free(&data, &cmd, &pids), 1);
	// if (!create_list_cmd(&cmd, argc, argv, 2))
	// 	return (error_free(&data, &cmd, &pids), 1);
	// cmd->in = data.infile;
	// if (!loop_process(&data, &pids, &cmd))
	// 	return (1);
	// wait_fct(&pids, &data, &cmd);
	// }
	free_outfile(&pipex.outfiles);
	close(pipex.infile);
	return (0);
}