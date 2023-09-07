/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:30:28 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/07 15:17:55 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	add_two_env(t_env *env, char *args, int to_equal)
{
	t_env	*new;

	if (to_equal == 1)
		new = ft_lstnew_env_equal(args);
	else
		new = ft_lstnew_env(args);
	if (!new)
		return (0);
	if (in_env(env, new->key))
		ft_lstreplace_env(&env, new);
	else
		ft_lstadd_back_env(&env, new);
	return (1);
}

int	add_no_equal(t_env *env, char *args)
{
	t_env	*newex;

	newex = ft_lstnew_env(args);
	if (!newex)
		return (0);
	if (!in_env(env, newex->key))
		ft_lstadd_back_env(&env, newex);
	else
		free(newex);
	return (1);
}

int	do_export(s_data *data, int i, char **args)
{
	if (ft_isdigit(args[i][0]) || is_inv(args[i]) || has_plus(args[i]))
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(args[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		i++;
		return (1);
	}
	if (ft_strrchr(args[i], '='))
	{
		if (!add_two_env(data->envex, args[i], 1))
			return (0);
		if (!add_two_env(data->envp, args[i], 0))
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
	if (!args[1])
		print_sorted_env(data->envex);
	else if (args[1])
	{
		i = 1;
		while (args[i])
		{
			if (!do_export(data, i, args))
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
