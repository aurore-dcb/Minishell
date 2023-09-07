/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:40:15 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/07 16:07:05 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_builtins(char *cmd, s_data *data)
{
	dprintf(1, "cmd = %s\n", cmd);
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(data));
	else if (!ft_strcmp(cmd, "cd"))
	{
		dprintf(1, "test\n");
		return (builtin_cd(data));
	}
	else if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(data));
	else if (!ft_strcmp(cmd, "env"))
		return (builtin_env(data));
	// else if (ft_strcmp(cmd, "exit"))
	// 	return (builtin_exit(data));
	else if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(data));
	else if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(data));
	return (1);
}
