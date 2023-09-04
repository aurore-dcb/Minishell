/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 11:22:02 by aducobu          ###   ########.fr       */
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

void	free_all(cmd_line **cmd, char *input)
{
	free(input);
	free_list(cmd);
}

void	free_outfile(t_outfile **outfiles)
{
	t_outfile	*tmp;

	while (*outfiles)
	{
		printf("ok\n");
		tmp = *outfiles;
		*outfiles = (*outfiles)->next;
		close(tmp->outfile);
		free(tmp);
	}
}