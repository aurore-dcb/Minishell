/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:01:33 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/05 10:28:50 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	if (!ft_isdigit(str[0]) && str[0] != '+' && str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	display_exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	num_exit(char *str, int error, t_data *data)
{
	long long int	exit_code;
	int				good;

	good = 0;
	if (!str)
		exit_code = data->exit_status;
	else if (error == 1)
	{
		display_exit_error(str);
		exit_code = 2;
	}
	else
	{
		exit_code = ft_long_atoi(str, &good);
		if (good == 1)
		{
			display_exit_error(str);
			exit_code = 2;
		}
		exit_code = exit_code % 256;
	}
	free_all(data);
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

int	builtin_exit(t_cmd_line *cmd, t_data *data)
{
	char	*str;
	int		error;

	error = 0;
	ft_putstr_fd("exit\n", 2);
	if (get_len_tab(cmd->args) > 1)
	{
		if (!is_str_digit(cmd->args[1]))
			error = 1;
		else if (get_len_tab(cmd->args) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			data->exit_status = 1;
			return (EXIT_FAILURE);
		}
	}
	if (cmd->args[1])
		str = ft_strdup(cmd->args[1]);
	else
		str = 0;
	num_exit(str, error, data);
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
