/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:37 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 17:17:11 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_pwd(void)
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
		g_exit = 1;
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	g_exit = 0;
	return (EXIT_SUCCESS);
}
