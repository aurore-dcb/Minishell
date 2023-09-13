/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:01:33 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/13 16:30:18 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	num_exit(char *str, int error)
{
	int	exit_code;

	if (!str)
		exit_code = 0;
	else if (error == 1)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	else
		exit_code = ft_atoi(str);
	free(str);
	exit(exit_code);
}

int	get_len_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	builtin_exit(s_data *data)
{
	char	*str;
	int		error;

	error = 0;
	ft_putstr_fd("exit\n", 2);
	if (get_len_tab(data->cmd->args) > 1)
	{
		if (!is_str_digit(data->cmd->args[1]))
			error = 1;
		else if (get_len_tab(data->cmd->args) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (data->cmd->args[1])
		str = ft_strdup(data->cmd->args[1]);
	else
		str = 0;
	free_all(data);
	num_exit(str, error);
	return (EXIT_SUCCESS);
}
