/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:04:51 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 14:19:48 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <dirent.h>

// modifier le PATH ?
// void builtin_cd(char *chemin)
// {
//     if (chdir(chemin) == -1)
//     {
//         perror("Error ");
//         return ;
//     }
// }

char	*find_path_ret(t_env *envp, char *str)
{
	t_env	*begin;

	begin = envp;
	while (begin)
	{
		if (!ft_strncmp(begin->data, str, ft_strlen(str)))
			return (ft_substr(begin->data, ft_strlen(str),
					ft_strlen(begin->data) - ft_strlen(str)));
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
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	change_path(s_data *data)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
	free(data->oldpwd);
	data->oldpwd = ft_strjoin("OLD", tmp);
	free(data->pwd);
	data->pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
}

int	build_cd(s_data *data)
{
	int		ret;

	if (!data->cmd->args[1] || ft_strncmp(data->cmd->args[1], "~", 1) == 0)
		ret = search_path(data->envp, "HOME=");
	else if (ft_strncmp(data->cmd->args[1], "-", 1) == 0)
		ret = search_path(data->envp, "OLDPWD=");
	else
	{
		ret = chdir(data->cmd->args[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(data->cmd->args[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(data);
	return (EXIT_SUCCESS);
}