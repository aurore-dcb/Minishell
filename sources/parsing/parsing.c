/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/30 11:54:09 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	expansion(s_data *data)
{
	token		*token;
	cmd_line	*begin;

	begin = data->cmd;
	if (!begin)
		return (0);
	while (begin)
	{
		token = begin->token;
		while (token)
		{
			if (token->type != LIMITOR)
			{
                token->word = ft_expand(token->word, data);
				if (!token->word)
					return (0);
			}
			token = token->next;
		}
		begin = begin->next;
	}
	return (1);
}

int	parsing(s_data *data)
{
	if (!data->env)
		return (0);
	if (closed_quotes(data->input, &data->etat) == 0)
		return (0);
	if (error_begin_end_cmd(data->input) == 1)
		return (0);
	if (error_double_pipe(data->input) == 1)
		return (0);
	if (!split_pipe(data->input, &data->cmd))
		return (0);
	if (error_syntax(&data->cmd))
		return (0);
	if (!expansion(data))
		return (0);
	return (1);
}
