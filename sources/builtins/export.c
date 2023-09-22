/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:30:28 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/22 13:58:16 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	add_two_env(t_env *env, char *args, int to_equal)
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
	if (in_env(env, new->key) && to_equal == 2)
	{
		ft_lstjoin_env(&env, new);
		free_env(new);
	}
	else if (in_env(env, new->key))
		ft_lstreplace_env(&env, new);
	else
		ft_lstadd_back_env(&env, new);
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

int	handle_equal(s_data *data, int i, char **args, int ret_inv)
{
	if (ret_inv == 2)
	{
		if (!add_two_env(data->envex, args[i], 2))
			return (0);
		if (!add_two_env(data->envp, args[i], 2))
			return (0);
	}
	else
	{
		if (!add_two_env(data->envex, args[i], 1))
			return (0);
		if (!add_two_env(data->envp, args[i], 0))
			return (0);
	}
	return (1);
}

int	do_export(s_data *data, int i, char **args)
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

int	builtin_export(s_data *data)
{
	char	**args;
	int		i;

	i = 0;
	args = data->cmd->args;
	data->exit_status = 0;
	if (!args[1])
		print_sorted_env(data->envex);
	else if (args[1])
	{
		i = 1;
		while (args[i])
		{
			if (!do_export(data, i, args))
			{
				data->exit_status = 1;
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
