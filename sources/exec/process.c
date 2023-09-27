/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:26:26 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 15:40:00 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	loop_process(s_data *data, t_pid **pids, pipex *pipex)
{
	cmd_line	*tmp;

	data->tab_env = list_to_tab(&data->envp);
	tmp = data->cmd;
	while (tmp)
	{
		if (!handle_hd(data, pids, pipex, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_parent(t_pid **pids, pid_t pid, cmd_line *cmd, t_file *last_in)
{
	ft_lstadd_back_pipex(pids, ft_lstnew_pipex(pid));
	if (cmd->fd[1] > 2)
		close(cmd->fd[1]);
	if (cmd->infile && last_in->fd > 2)
		close(last_in->fd);
}

int	ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data)
{
	pid_t	pid;
	t_file	*last_in;

	last_in = NULL;
	if (!cmd || (cmd->next && pipe(cmd->fd) == -1))
		return (0);
	if (cmd->next && cmd->next->infile == NULL)
		ft_lstadd_file(&cmd->next->infile, ft_lstnew_file(cmd->fd[0], 0, ""));
	else if (cmd->next && cmd->next->infile != NULL)
		close(cmd->fd[0]);
	last_in = ft_lstlast_file(cmd->infile);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (!ft_child(cmd, pipex, data, pids))
			return (0);
	}
	else
		ft_parent(pids, pid, cmd, last_in);
	return (1);
}

void	no_builtins(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids)
{
	if (!pipex->middle_cmd_path)
	{
		error_cmd(cmd, data);
		free_no_buil(cmd, pipex, data, pids);
		exit(127);
	}
	if (ft_strcmp(pipex->middle_cmd_path, ".") == 0)
		handle_point(cmd, pipex, data, pids);
	else if (execve(pipex->middle_cmd_path, cmd->args, data->tab_env) == -1)
	{
		free_no_buil(cmd, pipex, data, pids);
		exit(127);
	}
}

int	ft_child(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids)
{
	t_file	*last_in;
	t_file	*last_out;

	last_in = ft_lstlast_file(cmd->infile);
	last_out = ft_lstlast_file(cmd->outfile);
	if (last_in && last_in->fd == -1)
	{
		error_file(last_in, data);
		exit (data->exit_status);
	}
	if (last_out && last_out->fd == -1)
	{
		error_file(last_out, data);
		exit (data->exit_status);
	}
	do_dup(cmd, last_in, last_out);
	if (cmd->next)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (builtins_pipe(cmd->args[0], data, cmd) == 0)
		no_builtins(cmd, pipex, data, pids);
	free_no_buil(cmd, pipex, data, pids);
	exit(data->exit_status);
}
