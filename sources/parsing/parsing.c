/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 13:21:40 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_meta(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

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
				token->word = ft_expand(token->word, data, &token);
				// printf("token->word = %s\n",token->word);
				if (!token->word)
					return (0);
			}
			token = token->next;
			if (token)
				printf("TOKEN->word = %s\n", token->word);
		}
		begin = begin->next;
	}
	return (1);
}

int	parsing(s_data *data)
{
	char	tmp;

	if (closed_quotes(data->input, &data->etat) == 0)
		return (0);
	if (error_begin_end_cmd(data->input) == 1)
		return (error_token(data, '|'), 0);
	if (error_double_pipe(data->input) == 1)
		return (error_token(data, '|'), 0);
	if (!split_pipe(data->input, &data->cmd))
	{
		data->exit_status = 1;
		return (0);
	}
	tmp = error_syntax(&data->cmd);
	if (tmp)
		return (error_token(data, tmp), 0);
	if (error_syntax_alone(&data->cmd))
		return (error_token_gen(data), 0);
	if (!expansion(data))
		return (0);
	if (!tab_cmd(&data->cmd))
		return (0);
	return (1);
}
