/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:04:51 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/02 15:39:53 by rmeriau          ###   ########.fr       */
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
	ret = -1;
	if (tmp)
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

void	print_oldpwd(t_data *data, int ret)
{
	t_env	*tmp_env;

	if (ret)
		return ;
	tmp_env = data->envp;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, "OLDPWD", 6))
			printf("%s\n", tmp_env->data);
		tmp_env = tmp_env->next;
	}
}

int	builtin_cd(t_cmd_line *cmd, t_data *data)
{
	int		ret;
	char	*res;

	if (get_len_tab(cmd->args) > 2)
		return (error_message(data), EXIT_FAILURE);
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0
		|| ft_strncmp(cmd->args[1], "--", 2) == 0)
		ret = search_path(data->envp, "HOME");
	else if (ft_strncmp(cmd->args[1], "-", 1) == 0
		&& ft_strlen(cmd->args[1]) == 1)
	{
		ret = search_path(data->envp, "OLDPWD");
		print_oldpwd(data, ret);
	}
	else
		ret = error_path(cmd, data);
	if (ret != 0)
		return (EXIT_FAILURE);
	res = change_pwd(data);
	if (!change_oldpwd(data, res))
		return (EXIT_FAILURE);
	free(res);
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
