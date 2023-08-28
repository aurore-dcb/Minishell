/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:38:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/28 14:22:40 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

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
			free(cur_token->word);
			free(cur_token);
		}
		free(current);
	}
}
