/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:40:15 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/19 10:41:05 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtins_pipe(char *cmd, s_data *data, cmd_line *cmd_l)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", 3) && len == 3)
		return (builtin_pwd(), 1);
	else if (!ft_strncmp(cmd, "env", 3) && len == 3)
		return (builtin_env(data), 1);
	else if (!ft_strncmp(cmd, "unset", 5) && len == 5)
		return (builtin_unset(data), 1);
	else if (!ft_strncmp(cmd, "echo", 4) && len == 4)
		return (builtin_echo(cmd_l), 1);
	// else if (!ft_strncmp(cmd, "exit", 4) && len == 4)
	//     return (builtin_exit(data), 1);
	return (0);
}

int	builtins_no_pipe(cmd_line *cmd, s_data *data)
{
	int	len;

	if (cmd->in == -1)
	{
		error_file(cmd, data, 6);
		return (1);
	}
	if (cmd->args[0])
	{
		len = ft_strlen(cmd->args[0]);
		if (!ft_strncmp(cmd->args[0], "cd", 2) && len == 2)
			return ((builtin_cd(data)), 1);
		else if (!ft_strncmp(cmd->args[0], "export", 6) && len == 6)
			return (builtin_export(data), 1);
		else if (!ft_strncmp(cmd->args[0], "unset", 5) && len == 5)
			return (builtin_unset(data), 1);
	}
	return (0);
}
