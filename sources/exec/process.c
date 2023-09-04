/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:26:26 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 15:52:07 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	loop_process(s_data *data, t_pid **pids, pipex *pipex)
{
	cmd_line	*tmp;

	(void)pids;
	tmp = data->cmd;
	while (tmp)
	{
		// tmp->args = char **middle_cmd
		// pipex->middle_cmd = get_args(tmp->arg);
		// if (data->middle_cmd == NULL)
		// {
		// 	ft_printf("Error -> Command\n");
		// 	error_free(data, cmd, pids);
		// 	return (0);
		// }
		pipex->middle_cmd_path = find_path(pipex->paths, tmp->args[0]);
		if (!pipex->middle_cmd_path)
			return (0);
		printf("cmd path = %s\n", pipex->middle_cmd_path);
		// if (!data->middle_cmd_path)
		// 	return (error_free(data, cmd, pids),
		// 		ft_printf("Error-> Command\n"), 0);
		if (!ft_process(pipex, pids, tmp, data))
			return (ft_printf("Error-> Process\n"), 0);
		// return (error_free(data, cmd, pids),
		// 	ft_printf("Error-> Process\n"), 0);
		// free_tab(data->middle_cmd);
		// free(data->middle_cmd_path);
		free(pipex->middle_cmd_path);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data)
{
	pid_t	pid;

	if (!cmd || (cmd->next && pipe(pipex->fd) == -1))
		return (0);
	if (cmd->next && cmd->next->in == -2)
		cmd->next->in = pipex->fd[0];
	else if (cmd->next && cmd->next->in != -2)
		close(pipex->fd[0]);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (!ft_child(cmd, pipex, data))
			return (0);
	}
	else
	{
		ft_lstadd_back_pipex(pids, ft_lstnew_pipex(pid));
		if (pipex->fd[1] > 2)
			close(pipex->fd[1]);
		if (cmd->in > 2)
			close(cmd->in);
	}
	return (1);
}
int	ft_lstsize(t_env *lst)
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

char **list_to_tab(t_env **envp)
{
	int i;
	t_env *tmp;
	char **tab;
	
	tmp = *envp;
	if (!tmp)
		return (0);
	tab = malloc(sizeof(char *) * (ft_lstsize(*envp) + 1));
	if (!tab)
		return (0);
	i = 0;
	while (tmp)
	{
		tab[i] = malloc(sizeof(char) * (ft_strlen(tmp->data) + 1));
		if (!tab[i])
			return (0);
		tab[i] = ft_strcpy(tab[i], tmp->data, ft_strlen(tmp->data) + 1);
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

int	ft_child(cmd_line *cmd, pipex *pipex, s_data *data)
{
	if (cmd->in > 2)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->next)
	{
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
	}
	else
	{
		while (pipex->outfiles->next)
			pipex->outfiles = pipex->outfiles->next;
		dup2(pipex->outfiles->outfile, STDOUT_FILENO);
		close(pipex->outfiles->outfile);
	}
	if (execve(pipex->middle_cmd_path, cmd->args, list_to_tab(&data->envp)) == -1)
		return (close(pipex->fd[0]), close(pipex->fd[1]), 0);
	return (1);
}
