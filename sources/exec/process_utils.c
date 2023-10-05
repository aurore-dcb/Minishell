/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:08:58 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/05 10:29:07 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**copy_to_tab(char **tab, t_env *tmp)
{
	char	*ctmp;
	int		i;

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

char	**list_to_tab(t_env **envp)
{
	t_env	*tmp;
	char	**tab;

	tmp = *envp;
	if (!tmp)
		return (0);
	tab = malloc(sizeof(char *) * (ft_lstsize(*envp) + 1));
	if (!tab)
		return (0);
	tab = copy_to_tab(tab, tmp);
	if (!tab)
		return (0);
	return (tab);
}

int	handle_hd(t_data *data, t_pid **pids, t_pipex *pipex, t_cmd_line *tmp)
{
	if (is_here_doc(tmp))
	{
		if (!ft_hd(tmp, pipex, data, pids))
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
			return (free(pipex->middle_cmd_path), 0);
		free(pipex->middle_cmd_path);
	}
	return (1);
}

void	handle_pt(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids)
{
	char	**tab;

	tab = new_tab(cmd->args, get_len_tab(cmd->args));
	if (!tab)
	{
		fr_no_buil(cmd, pipex, data, pids);
		exit(1);
	}
	if (execve(cmd->args[1], tab, data->tab_env) == -1)
		error_file_exec(cmd->args[1], data, errno);
	free_tab(tab);
	fr_no_buil(cmd, pipex, data, pids);
	exit(126);
}

void	do_dup(t_cmd_line *cmd, t_file *last_in, t_file *last_out)
{
	if (last_in && last_in->fd > 2)
	{
		dup2(last_in->fd, STDIN_FILENO);
		close(last_in->fd);
	}
	if (last_out && last_out->fd > 2)
	{
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
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
}
