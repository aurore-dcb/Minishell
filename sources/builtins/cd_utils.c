/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:29:26 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/21 12:04:56 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*change_pwd(s_data *data)
{
	t_env	*tmp_env;
	char	*ret;

	tmp_env = data->envp;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, "PWD", 3))
		{
			ret = ft_strdup(tmp_env->data);
			if (!ret)
				return (NULL);
			free(tmp_env->data);
			tmp_env->data = getcwd(NULL, 0);
		}
		tmp_env = tmp_env->next;
	}
	return (ret);
}

int	change_oldpwd(s_data *data, char *ret)
{
	t_env	*tmp_env;

	if (!ret)
		return (0);
	tmp_env = data->envp;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, "OLDPWD", 6))
		{
			free(tmp_env->data);
			tmp_env->data = ft_strdup(ret);
			if (!tmp_env->data)
				return (0);
		}
		tmp_env = tmp_env->next;
	}
	return (1);
}

int	error_path(s_data *data)
{
	int	ret;

	ret = chdir(data->cmd->args[1]);
	if (ret != 0)
	{
		data->exit_status = 1;
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(data->cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (ret);
}

void	error_message(s_data *data)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
}
