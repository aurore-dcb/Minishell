/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:13 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/15 15:50:27 by rmeriau          ###   ########.fr       */
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

void	error_file(cmd_line *cmd, s_data *data, t_type type)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(get_info_cmd(cmd, type), 2);
	if (cmd->error == 13)
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
