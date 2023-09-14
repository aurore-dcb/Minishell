/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/14 10:13:38 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialise_pipex(pipex *pipex)
{
	pipex->paths = NULL;
	pipex->infile = -2;
	pipex->here_doc_file = -1;
	// pipex->middle_cmd = NULL;
	pipex->middle_cmd_path = NULL;
}

int	parsing_pipex(pipex *pipex, s_data *data)
{
	pipex->paths = get_paths(&data->envp);
	// if (!pipex->paths)
	// 	return (ft_printf("ERROR -> Paths\n"), 0);
	if (!open_infile(pipex, data))
		return (ft_printf("ERROR -> Can't open infile\n"), 0);
	if (!open_outfile(pipex, data))
	{
		// close(pipex->infile);
		return (ft_printf("ERROR -> Can't open outfile\n"), 0);
	}
	return (1);
}

int	ft_lstsize_cmd(cmd_line *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_pipex(s_data *data)
{
	t_pid *pids;
	pipex pipex;

	if (!ft_strcmp(data->cmd->args[0], "exit") && ft_lstsize_cmd(data->cmd) == 1)
		builtin_exit(data);
	pids = NULL;
	initialise_pipex(&pipex);
	if (!parsing_pipex(&pipex, data))
		return (1);
	data->cmd->in = pipex.infile;
	if (!loop_process(data, &pids, &pipex))
		return (free_tab(pipex.paths), free(pids), printf("error loop process\n"), 1);
	wait_fct(&pids);
	free_tab(pipex.paths);
	return (0);
}
