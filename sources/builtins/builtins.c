/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:40:15 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/02 17:05:19 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtins_pipe(char *cmd, t_data *data, t_cmd_line *cmd_l)
{
	int	len;

	len = ft_strlen(cmd);
	if (len != 0)
	{
		if (!ft_strcmp(cmd, ".") && !cmd_l->args[1])
			return (error_token_gen(data, 2), 1);
		else if ((!ft_strncmp(cmd, "cd", 2) && len == 2)
			|| (!ft_strncmp(cmd, "unset", 5) && len == 5))
			return (1);
		else if (!ft_strncmp(cmd, "pwd", 3) && len == 3)
			return (builtin_pwd(data), 1);
		else if (!ft_strncmp(cmd, "env", 3) && len == 3)
			return (builtin_env(data), 1);
		else if (!ft_strncmp(cmd, "echo", 4) && len == 4)
			return (builtin_echo(cmd_l, data), 1);
		else if (!ft_strncmp(cmd, "exit", 4) && len == 4)
			return (1);
		else if (!ft_strncmp(cmd_l->args[0], "export", 6) && len == 6)
			return (builtin_export(cmd_l, data), 1);
	}
	else
		return (1);
	return (0);
}

int	builtins_no_pipe(t_cmd_line *cmd, t_data *data)
{
	int	len;

	len = 0;
	if (cmd->args[0])
	{
		len = ft_strlen(cmd->args[0]);
		if (!ft_strncmp(cmd->args[0], "cd", 2)
			&& len == 2 && ft_lstsize_cmd(cmd) == 1)
			return ((builtin_cd(cmd, data)), 1);
		else if (!ft_strncmp(cmd->args[0], "export", 6) && len == 6
			&& cmd->args[1])
			return (builtin_export(cmd, data), 1);
		else if (!ft_strncmp(cmd->args[0], "unset", 5) && len == 5)
			return (builtin_unset(cmd, data), 1);
	}
	return (0);
}

void	do_join(t_env *list, t_env *new)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(list->key, new->key))
	{
		if (list->data && ft_strcmp(list->data, "") != 0)
		{
			tmp = ft_strdup(list->data);
			free(list->data);
		}
		if ((new->data && ft_strcmp(new->data, "") != 0)
			|| (tmp && ft_strcmp(tmp, "") != 0))
		{
			list->data = ft_strjoin(tmp, new->data);
			free(tmp);
		}
	}
}
