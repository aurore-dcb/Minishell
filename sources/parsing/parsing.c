/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 17:18:21 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_meta(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_spaces(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	expansion(t_data *data)
{
	t_token		*token;
	t_cmd_line	*begin;

	begin = data->cmd;
	if (!begin)
		return (0);
	while (begin)
	{
		token = begin->token;
		while (token)
		{
			token->word = ft_expand(token->word, data, &token, 0);
			if (!token->word)
				return (0);
			token = token->next;
		}
		begin = begin->next;
	}
	return (1);
}

int	error_pars(t_data *data)
{
	if (closed_quotes(data->input, &data->etat) == 0)
		return (parse_error(data), 0);
	if (error_begin_end_cmd(data->input) == 1)
		return (error_token(data, '|'), 0);
	if (error_double_pipe(data->input) == 1)
		return (error_token(data, '|'), 0);
	if (error_pipe_token(data->input) == 1)
		return (error_token(data, '|'), 0);
	if (!split_pipe(data->input, &data->cmd))
	{
		g_exit = 1;
		return (parse_error(data), 0);
	}
	return (1);
}

int	parsing(t_data *data)
{
	char	tmp;

	if (!error_pars(data))
		return (0);
	tmp = error_syntax(&data->cmd);
	if (tmp)
		return (error_token(data, tmp), 0);
	if (error_syntax_alone(&data->cmd) == 1)
		return (error_token_gen(data, 1), 0);
	else if (error_syntax_alone(&data->cmd) == 2)
		return (error_token_gen(data, 2), 0);
	if (!expansion(data))
		return (0);
	if (!tab_cmd(&data->cmd))
		return (0);
	return (1);
}
