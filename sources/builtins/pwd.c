/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:37 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/21 12:07:14 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_pwd(s_data *data)
{
	char	*res;

	res = getcwd(NULL, 0);
	if (res)
	{
		printf("%s\n", res);
		free(res);
	}
	else
	{
		data->exit_status = 1;
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
