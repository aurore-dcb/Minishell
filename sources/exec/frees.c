/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 14:53:43 by aducobu          ###   ########.fr       */
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

void	free_list(t_cmd_line *begin)
{
	t_cmd_line	*current;
	t_token		*cur_token;

	while (begin != NULL)
	{
		current = begin;
		begin = begin->next;
		if (current->infile)
			free_cmd_in(current->infile);
		if (current->outfile)
			free_cmd_in(current->outfile);
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

void	free_all(t_data *data)
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

void	wait_fct(t_pid **pids, t_data *data)
{
	t_pid	*tmp;

	(void)data;
	tmp = *pids;
	while (tmp)
	{
		waitpid((tmp->pid), &g_exit, 0);
		tmp = tmp->next;
	}
	free_pid(pids);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
	{
		if (g_exit == SIGTERM)
		{
			g_exit = 143;
			ft_putstr_fd("Terminated\n", 2);
		}
		if (g_exit == SIGINT)
			g_exit = 130;
	}
}
