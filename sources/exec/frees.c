/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/18 13:41:33 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
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
		if (current->in > 2)
			close (current->in);
		if (current->out > 2)
			close (current->out);
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
	if (data->tab_env)
		free_tab(data->tab_env);
}

void	wait_fct(t_pid **pids, s_data *data)
{
	t_pid	*tmp;

	while (*pids)
	{
		tmp = *pids;
		if (waitpid(((*pids)->pid), &data->exit_status, 0) == -1)
		{
			dprintf(1, "erreur wait\n");
		}
		*pids = (*pids)->next;
		// dprintf(1, "FREE PID\n");
		free(tmp);
	}
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
	{
		if (data->exit_status == SIGTERM)
			ft_putstr_fd("Terminated\n", 2);
		data->exit_status += 128;
	}
}
