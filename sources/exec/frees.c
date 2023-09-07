/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/07 15:06:40 by aducobu          ###   ########.fr       */
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

void	free_list(cmd_line **begin)
{
	cmd_line	*current;
	token		*cur_token;

	while (*begin != NULL)
	{
		current = *begin;
		(*begin) = (*begin)->next;
		free(current->cmd);
		while (current->token)
		{
			cur_token = current->token;
			current->token = cur_token->next;
			if (cur_token->word)
				free(cur_token->word);
			free(cur_token);
		}
		free(current);
	}
}

// void free_outfiles(t_outfile **outfiles)
// {
// 	t_outfile *current;

// 	if (*outfiles)
// 	{
// 		current = *outfiles;
// 		*outfiles = (*outfiles)->next;
// 		if (current->outfile)
// 		{
// 			close(current->outfile);
// 		}
// 		free(*outfiles);
// 	}
// }

void	free_all(cmd_line **cmd, char *input, pipex *pipex)
{
	free(input);
	if (pipex->infile > 1)
		close(pipex->infile);
	// if (pipex->outfiles)
	// 	free_outfiles(&pipex->outfiles);
	if (pipex->paths)
		free_tab(pipex->paths);
	if (cmd)
		free_list(cmd);
}

// void	free_outfile(t_outfile **outfiles)
// {
// 	t_outfile	*tmp;

// 	while (*outfiles)
// 	{
// 		tmp = *outfiles;
// 		*outfiles = (*outfiles)->next;
// 		close(tmp->outfile);
// 		free(tmp);
// 	}
// }

void	wait_fct(t_pid **pids, pipex *pipex, s_data *data)
{
	(void)data;
	(void)pipex;
	t_pid	*tmp;

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
