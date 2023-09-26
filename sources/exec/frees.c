/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/26 11:10:50 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_cmd_in(t_file *in)
{	
	t_file	*current;

	while (in)
	{
		current = in;
		in = in->next;
		if (current->fd > 2)
			close(current->fd);
		if (current->name)
			free(current->name);
		free(current);
	}
}

void	free_list(cmd_line *begin)
{
	cmd_line	*current;
	token		*cur_token;

	while (begin != NULL)
	{
		current = begin;
		begin = begin->next;
		if (current->infile)
			free_cmd_in(current->infile);
			// free list de infile
		if (current->outfile)
			free_cmd_in(current->outfile);
		// 	close(current->in);
		// if (current->out > 2)
		// 	close(current->out);
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
	if (data->tab_env)
		free_tab(data->tab_env);
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

void	wait_fct(t_pid **pids, s_data *data)
{
	t_pid	*tmp;

	tmp = *pids;
	while (tmp)
	{
		waitpid((tmp->pid), &data->exit_status, 0);
		tmp = tmp->next;
	}
	free_pid(pids);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
	{
		if (data->exit_status == SIGTERM)
		{
			data->exit_status = 143;
			ft_putstr_fd("Terminated\n", 2);
		}
		if (data->exit_status == SIGINT)
			data->exit_status = 130;
	}
}
