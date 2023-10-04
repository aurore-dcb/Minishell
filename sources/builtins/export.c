/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:30:28 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/02 14:00:01 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	add_to_envp(char *args, int to_equal, t_data *data)
{
	t_env	*new;

	if (to_equal >= 1)
		new = ft_lstnew_env_equal(args);
	else
		new = ft_lstnew_env(args);
	if (!new)
		return (0);
	if (to_equal == 2)
		del_plus(new->key, '+');
	if (in_env(data->envp, new->key) && to_equal == 2)
	{
		ft_lstjoin_env(&data->envp, new);
		free_env(new);
	}
	else if (in_env(data->envp, new->key))
		ft_lstreplace_env(&data->envp, new);
	else
		ft_lstadd_back_env(&data->envp, new);
	return (1);
}

int	add_to_envex(char *args, int to_equal, t_data *data)
{
	t_env	*new;

	if (to_equal >= 1)
		new = ft_lstnew_env_equal(args);
	else
		new = ft_lstnew_env(args);
	if (!new)
		return (0);
	if (to_equal == 2)
		del_plus(new->key, '+');
	if (in_env(data->envex, new->key) && to_equal == 2)
	{
		ft_lstjoin_env(&data->envex, new);
		free_env(new);
	}
	else if (in_env(data->envex, new->key))
		ft_lstreplace_env(&data->envex, new);
	else
		ft_lstadd_back_env(&data->envex, new);
	return (1);
}

int	add_no_equal(t_env *env, char *args)
{
	t_env	*newex;

	newex = ft_lstnew_env_no_equal(args);
	if (!newex)
		return (0);
	if (!in_env(env, newex->key))
		ft_lstadd_back_env(&env, newex);
	else
		free(newex);
	return (1);
}

int	do_export(t_data *data, int i, char **args)
{
	int	ret_inv;

	ret_inv = is_inv(args[i]);
	if (ft_isdigit(args[i][0]) || (ret_inv == 1) || has_plus(args[i]))
	{
		data->exit_status = 1;
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		i++;
		return (1);
	}
	if (ft_strrchr(args[i], '='))
	{
		if (!handle_equal(data, i, args, ret_inv))
			return (0);
	}
	else if (!ft_strrchr(args[i], '='))
	{
		if (!add_no_equal(data->envex, args[i]))
			return (0);
	}
	return (1);
}

int	builtin_export(t_cmd_line *cmd, t_data *data)
{
	char	**args;
	int		i;

	signal(SIGPIPE, SIG_IGN);
	i = 1;
	args = cmd->args;
	data->exit_status = 0;
	if (!args[1])
		print_sorted_env(data->envex);
	else if (args[1])
	{
		while (args[i])
		{
			if (!(args[i][0] == '_' && args[i][1] == '='))
			{
				if (!do_export(data, i, args))
				{
					data->exit_status = 1;
					return (EXIT_FAILURE);
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
