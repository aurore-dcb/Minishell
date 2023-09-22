/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:06:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 14:06:04 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	end_except(char *cmd, int i)
{
	if (cmd[i] == '<')
	{
		i++;
		if (cmd[i] == '<')
			i++;
		return (i);
	}
	if (cmd[i] == '>')
	{
		i++;
		if (cmd[i] == '>')
			i++;
		return (i);
	}
	return (i);
}

char	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	get_end_word(char *cmd, int i)
{
	int		tmp;

	tmp = end_except(cmd, i);
	if (tmp != i)
		return (tmp);
	while (cmd[tmp])
	{
		if (cmd[tmp] == 39)
		{
			tmp++;
			while (cmd[tmp] && cmd[tmp] != 39)
				tmp++;
		}
		else if (cmd[tmp] == 34)
		{
			tmp++;
			while (cmd[tmp] && cmd[tmp] != 34)
				tmp++;
		}
		else if (cmd[tmp] == ' ' || cmd[tmp] == '<' || cmd[tmp] == '>')
			return (tmp);
		tmp++;
	}
	return (tmp);
}
