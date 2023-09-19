/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:04:51 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/19 15:56:34 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_path_ret(t_env *envp, char *str)
{
	t_env	*begin;

	begin = envp;
	while (begin)
	{
		if (!ft_strncmp(begin->key, str, ft_strlen(str)))
			return (begin->data);
		begin = begin->next;
	}
	return (NULL);
}

int	search_path(t_env *envp, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(envp, str);
	ret = chdir(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str));
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

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

int	builtin_cd(s_data *data)
{
	int		ret;
	char	*res;

	if (!data->cmd->args[1] || ft_strncmp(data->cmd->args[1], "~", 1) == 0)
		ret = search_path(data->envp, "HOME");
	else if (ft_strncmp(data->cmd->args[1], "-", 1) == 0 && ft_strlen(data->cmd->args[1]) == 1)
	{
		ret = search_path(data->envp, "OLDPWD");
		// affichage chemin cd -
	}
	else
	{
		ret = chdir(data->cmd->args[1]);
		if (ret != 0)
		{
			ft_putstr_fd("bash: cd: ", STDERR_FILENO);
			ft_putstr_fd(data->cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	res = change_pwd(data);
	if (!change_oldpwd(data, res))
		return (EXIT_FAILURE);
	free(res);
	return (EXIT_SUCCESS);
}
