/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 18:33:35 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialise_pipex(t_pipex *pipex)
{
	pipex->paths = NULL;
	pipex->here_doc_file = -1;
	pipex->middle_cmd_path = NULL;
}

int	parsing_pipex(t_pipex *pipex, t_data *data)
{
	pipex->paths = get_paths(&data->envp);
	if (!open_files(data))
	{
		g_exit = 1;
		return (0);
	}
	return (1);
}

int	ft_lstsize_cmd(t_cmd_line *lst)
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

int	ft_pipex(t_data *data)
{
	t_pid	*pids;
	t_pipex	pipex;

	if (data->cmd->args[0] && !ft_strcmp(data->cmd->args[0], "exit")
		&& ft_lstsize_cmd(data->cmd) == 1)
		builtin_exit(data->cmd, data);
	set_signals(2);
	pids = NULL;
	initialise_pipex(&pipex);
	if (!parsing_pipex(&pipex, data))
		return (1);
	if (!loop_process(data, &pids, &pipex))
		return (free_tab(pipex.paths), free(pids), 0);
	wait_fct(&pids);
	free_tab(pipex.paths);
	return (1);
}
