/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/12 17:06:25 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(cmd_line *begin)
{
	cmd_line	*current;
	token		*cur_token;

	while (begin != NULL)
	{
		current = begin;
		begin = begin->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_tab(current->args);
		while (current->token)
		{
			cur_token = current->token;
			current->token = cur_token->next;
			if (cur_token->word != NULL)
				free(cur_token->word);
			free(cur_token);
		}
		free(current);
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->data);
		free(temp);
	}
}

void	free_all(s_data *data)
{
	if (data->input)
		free(data->input);
	if (data->cmd)
		free_list(data->cmd);
	if (data->envp)
		free_env(data->envp);
	if (data->envex)
		free_env(data->envex);
}

void	wait_fct(t_pid **pids, pipex *pipex, s_data *data)
{
	t_pid	*tmp;

	(void)data;
	(void)pipex;
	// close(pipex->fd[0]);
	// close(pipex->fd[1]);
	while (*pids)
	{
		tmp = *pids;
		// dprintf(1, "WAIT\n");
		waitpid(((*pids)->pid), NULL, 0);
		*pids = (*pids)->next;
		free(tmp);
	}
	// free(*pids);
	// free(data->input);
	// if (pipex->infile > 1)
	// 	close(pipex->infile);
	// if (pipex->outfiles)
	// 	free_outfiles(&pipex->outfiles);
	// free_all(&data->cmd, data->input, pipex);
}
