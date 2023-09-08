/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:40:15 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/08 11:55:43 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtins_pipe(char *cmd, s_data *data)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(data), 0);
	else if (!ft_strcmp(cmd, "env"))
		return (builtin_env(data), 0);
	else if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(data), 0);
	else if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(data), 0);
	// else if (ft_strcmp(cmd, "exit"))
	// 	return (builtin_exit(data));
	return (1);
}

int builtins_no_pipe(char *cmd, s_data *data)
{
	int len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", 2) &&  len == 2)
		return ((builtin_cd(data)), 1);
	else if (!ft_strncmp(cmd, "export", 6) &&  len == 6)
		return (builtin_export(data), 1);
	else if (!ft_strncmp(cmd, "unset", 5) && len == 5)
		return (builtin_unset(data), 1);
	return (0);
}