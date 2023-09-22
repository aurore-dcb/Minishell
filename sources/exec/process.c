/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:26:26 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 14:14:07 by aducobu          ###   ########.fr       */
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
		if (is_here_doc(tmp))
		{
			if (!ft_here_doc(tmp, pipex, data, pids))
			{
				data->exit_status = 1;
				return (unlink(".here_doc"), 0);
			}
		}
		else
		{
			if (builtins_no_pipe(tmp, data))
				return (1);
			pipex->middle_cmd_path = find_path(pipex->paths, tmp->args[0]);
			if (!ft_process(pipex, pids, tmp, data))
				return (0);
			free(pipex->middle_cmd_path);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data)
{
	pid_t	pid;
	t_infile *last;

	last = NULL;
	if (!cmd || (cmd->next && pipe(cmd->fd) == -1))
		return (0);
	if (cmd->next && cmd->next->infile == NULL)
		ft_lstadd_back_infile(&cmd->next->infile, ft_lstnew_infile(cmd->fd[0], 0));
	else if (cmd->next && cmd->next->infile != NULL)
		close(cmd->fd[0]);
	last = ft_lstlast_infile(cmd->infile);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (!ft_child(cmd, pipex, data, pids))
			return (0);
	}
	else
	{
		ft_lstadd_back_pipex(pids, ft_lstnew_pipex(pid));
		if (cmd->fd[1] > 2)
			close(cmd->fd[1]);
		if (cmd->infile && last->fd > 2)
			close(last->fd);
	}
	return (1);
}

// void redirections()

int	ft_child(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids)
{
	t_infile *last;

	last = ft_lstlast_infile(cmd->infile);
	if (last && last->fd == -1)
	{
		error_file(cmd, last, data, 6);
		return (0);
	}
	// // si un des infile == -1
	// if (cmd->out == -1)
	// {
	// 	error_file(cmd, data, 8);
	// 	return (0);
	// }
	if (last && last->fd > 2)
	{
		dup2(last->fd, STDIN_FILENO);
		close(last->fd);
	}
	if (cmd->out > 2)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else if (cmd->next)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	if (cmd->next)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (builtins_pipe(cmd->args[0], data, cmd) == 0)
    {
        if (!pipex->middle_cmd_path)
        {
            error_cmd(cmd, data);
            free_tab(pipex->paths);
            free_all(data);
            exit(127);
        }
        if (strcmp(pipex->middle_cmd_path, ".") == 0)
        {
            char **tab = new_tab(cmd->args, get_len_tab(cmd->args));
            if (execve(cmd->args[1], tab, data->tab_env) == -1)
                error_file_exec(cmd->args[1], data, errno);
            free(pipex->middle_cmd_path);
            return (free_tab(tab), close(cmd->fd[0]), close(cmd->fd[1]), 0);
        }
        else if (execve(pipex->middle_cmd_path, cmd->args, data->tab_env) == -1)
            return (close(cmd->fd[0]), close(cmd->fd[1]), 0);
    }
    free(pipex->middle_cmd_path);
    free_tab(pipex->paths);
    free_all(data);
    free_pid(pids);
    exit(data->exit_status);
}

void    error_file_exec(char *cmd, s_data *data, int error)
{
    data->exit_status = 1;
    ft_putstr_fd("bash: ", 2);
    ft_putstr_fd(cmd, 2);
    if (error == 13)
        ft_putstr_fd(": Permission denied\n", 2);
    else
        ft_putstr_fd(": No such file or directory\n", 2);
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

char	**list_to_tab(t_env **envp)
{
	int		i;
	t_env	*tmp;
	char	**tab;
	char	*ctmp;

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
		{
			ctmp = ft_strjoin(tmp->key, "=");
			tab[i] = ft_strjoin(ctmp, tmp->data);
			free(ctmp);
		}
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
