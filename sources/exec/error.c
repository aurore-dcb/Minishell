/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:13 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/28 10:30:32 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	error_file(t_file *in, t_data *data)
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

void	error_cmd(t_cmd_line *cmd, t_data *data)
{
	data->exit_status = 127;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_token_gen(t_data *data, int tmp)
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

void	error_token(t_data *data, char c)
{
	data->exit_status = 2;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

void	error_file_exec(char *cmd, t_data *data, int error)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	if (error == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}
