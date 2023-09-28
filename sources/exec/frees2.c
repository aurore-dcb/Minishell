/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:23:18 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/28 10:57:39 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_elem_env(t_env *list)
{
	if (list->data && ft_strcmp(list->data, "") != 0)
		free(list->data);
	if (list->key)
		free(list->key);
	if (list)
		free(list);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free_elem_env(temp);
	}
}

void	fr_no_buil(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids)
{
	if (pipex->middle_cmd_path)
		free(pipex->middle_cmd_path);
	free_tab(pipex->paths);
	if (cmd->fd[0] >= 0)
		close(cmd->fd[0]);
	if (cmd->fd[1] >= 0)
		close(cmd->fd[1]);
	free_all(data);
	free_pid(pids);
}

void	free_pid(t_pid **pids)
{
	t_pid	*tmp;

	while (*pids)
	{
		tmp = *pids;
		*pids = (*pids)->next;
		free(tmp);
	}
}
