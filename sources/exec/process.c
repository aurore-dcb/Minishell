/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:26:26 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/13 15:27:09 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void affichage(cmd_line **cmd, pipex *pipex)
{
	dprintf(1, "----------------debut---------------\n");
	cmd_line	*tmp;
	tmp = *cmd;
	dprintf(1, "commande : %s\n", tmp->cmd);
	int i = 0;
	while (tmp->args[i])
	{
		dprintf(1, "arg = %s\n", tmp->args[i]);
		i++;
	}
	dprintf(1, "cmd path = %s\n", pipex->middle_cmd_path);
	dprintf(1, "-----------------fin--------------\n");
}

int	loop_process(s_data *data, t_pid **pids, pipex *pipex)
{
	cmd_line	*tmp;

	data->tab_env = list_to_tab(&data->envp);
	tmp = data->cmd;
	while (tmp)
	{
		if (is_here_doc(tmp))
		{
			if (!ft_here_doc(tmp, pipex, data, pids))
				return (dprintf(1, "erreur here_doc\n"), 0);
			return (unlink(".here_doc"), 1);
		}
		if (builtins_no_pipe(tmp->args[0], data))
			return (1);
		pipex->middle_cmd_path = find_path(pipex->paths, tmp->args[0]);
		if (!pipex->middle_cmd_path)
			return (0);
		if (!ft_process(pipex, pids, tmp, data))
			return (ft_printf("Error-> Process\n"), 0);
		free(pipex->middle_cmd_path);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data)
{
	pid_t	pid;

	if (!cmd || (cmd->next && pipe(cmd->fd) == -1))
		return (0);
	if (cmd->next && cmd->next->in == -2)
		cmd->next->in = cmd->fd[0];
	else if (cmd->next && cmd->next->in != -2)
		close(cmd->fd[0]);
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
		if (cmd->fd[1] > 2)
			close(cmd->fd[1]);
		if (cmd->in > 2)
			close(cmd->in);
	}
	return (1);
}

int	ft_child(cmd_line *cmd, pipex *pipex, s_data *data)
{
	if (cmd->in == -1 || cmd->out == -1)
		return (dprintf(1, "ERROR infile or outfile == -1\n"), 0);
	if (cmd->in > 2)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out > 2)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else if (cmd->next)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->next)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (builtins_pipe(cmd->args[0], data) == 0)
	{
		if (execve(pipex->middle_cmd_path, cmd->args, data->tab_env) == -1)
			return (close(cmd->fd[0]), close(cmd->fd[1]), 0);
	}
	free(pipex->middle_cmd_path);
	free_tab(pipex->paths);
    free_all(data);
    exit(0);
	// return(1);
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
        if (tmp->data)
            tab[i] = ft_strdup(tmp->data);
        else
            tab[i] = ft_strdup("");
        if (!tab[i])
            return (0);
        i++;
        tmp = tmp->next;
    }
	tab[i] = NULL;
	return (tab);
}
