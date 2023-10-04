/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:28:45 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/02 13:52:48 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_shlvl(t_data *data)
{
	t_env	*tmp_env;
	int		ret;

	tmp_env = data->envp;
	ret = 0;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, "SHLVL", 5))
			ret = ft_atoi(tmp_env->data);
		tmp_env = tmp_env->next;
	}
	return (ret);
}

int	is_shlvl(t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->envp;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, "SHLVL", 5))
			return (1);
		tmp_env = tmp_env->next;
	}
	return (0);
}

char	*get_shvalue(t_data *data)
{
	int	old_shlevel;

	old_shlevel = get_shlvl(data) + 1;
	if (old_shlevel >= 999)
	{
		ft_putstr_fd("bash: warning: shell level (", 2);
		ft_putstr_fd(ft_itoa(old_shlevel), 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		old_shlevel = 1;
	}
	else if (old_shlevel < 0)
		old_shlevel = 0;
	return (ft_itoa(old_shlevel));
}

void	handle_shlevel(t_data *data)
{
	char	*sh_value;
	char	*tmp;
	t_env	*new;
	t_env	*newex;

	if (!is_shlvl(data))
	{
		new = ft_lstnew_env("SHLVL=1");
		if (!new)
			return ;
		ft_lstadd_back_env(&data->envp, new);
		return ;
	}
	sh_value = get_shvalue(data);
	tmp = ft_strjoin("SHLVL=", sh_value);
	new = ft_lstnew_env(tmp);
	free(sh_value);
	ft_lstreplace_env(&data->envp, new);
	newex = ft_lstnew_env(tmp);
	ft_lstreplace_env(&data->envex, newex);
	free(tmp);
}
