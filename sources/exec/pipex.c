/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 11:37:11 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialise_pipex(pipex *pipex)
{
	pipex->paths = NULL;
	pipex->here_doc_file = -1;
	pipex->middle_cmd_path = NULL;
}

int	parsing_pipex(pipex *pipex, s_data *data)
{
	pipex->paths = get_paths(&data->envp);
	if (!open_files(data))
	{
		data->exit_status = 1;
		return (0);
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

int    ft_pipex(s_data *data)
{
    t_pid    *pids;
    pipex    pipex;

    if (data->cmd->args[0] && !ft_strcmp(data->cmd->args[0], "exit")
        && ft_lstsize_cmd(data->cmd) == 1)
        builtin_exit(data);
    if (data->cmd->args[0] && !ft_strcmp(data->cmd->args[0], "./minishell")
        && ft_lstsize_cmd(data->cmd) == 1)
        set_signals(4);
    else
        set_signals(2);
    pids = NULL;
    initialise_pipex(&pipex);
    if (!parsing_pipex(&pipex, data))
        return (1);
    if (!loop_process(data, &pids, &pipex))
        return (free_tab(pipex.paths), free(pids), 0);
    wait_fct(&pids, data);
    free_tab(pipex.paths);
    return (1);
}
