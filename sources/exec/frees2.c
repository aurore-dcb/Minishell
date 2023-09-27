/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:23:18 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/27 11:07:09 by aducobu          ###   ########.fr       */
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
void    free_no_buil(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids)
{
    if (pipex->middle_cmd_path)
        free(pipex->middle_cmd_path);
    free_tab(pipex->paths);
    free_all(data);
    free_pid(pids);
    if (cmd->fd[0] >= 0)
        close(cmd->fd[0]);
    if (cmd->fd[1] >= 0)
        close(cmd->fd[1]);
}
