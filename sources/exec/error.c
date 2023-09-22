/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:13 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/22 15:41:22 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_info_cmd(cmd_line *beg_cmd, t_type type)
{
	token		*beg_token;

	if (!beg_cmd)
		return (NULL);
	beg_token = beg_cmd->token;
	if (!beg_token)
		return (NULL);
	while (beg_token)
	{
		if (beg_token->type == type)
			return (beg_token->word);
		beg_token = beg_token->next;
	}
	return (NULL);
}

void	error_file(cmd_line *cmd, t_file *in, s_data *data, t_type type)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(get_info_cmd(cmd, type), 2);
	if (in->r_no == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_cmd(cmd_line *cmd, s_data *data)
{
	data->exit_status = 127;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_token_gen(s_data *data, int tmp)
{
	data->exit_status = 2;
	if (tmp == 1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (tmp == 2)
	{
		ft_putstr_fd("bash: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	}
}

void	error_token(s_data *data, char c)
{
	data->exit_status = 2;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}
