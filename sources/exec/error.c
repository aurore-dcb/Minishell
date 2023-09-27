/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:13 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/27 11:37:43 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	error_file(t_file *in, s_data *data)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(in->name, 2);
	if (in->r_no == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (in->r_no == 21)
		ft_putstr_fd(": Is a directory\n", 2);
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
