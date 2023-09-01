/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:37 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 14:09:50 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// gerer argument
// void	builtin_pwd(char **env)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 4;
// 	if (!env)
// 		return ;
// 	while (env[i])
// 	{
// 		if (ft_strnstr(env[i], "PWD=", 4))
// 		{
// 			while (env[i][j])
// 			{
// 				printf("%c", env[i][j]);
// 				j++;
// 			}
// 			printf("\n");
// 			return ;
// 		}
// 		i++;
// 	}
// }

void	builtin_pwd(s_data *data)
{
	int		i;

	if (!data->pwd)
		return ;
	i = 4;
	while (data->pwd[i])
	{
		ft_putchar_fd(data->pwd[i], 1);
		i++;
	}
	printf("\n");
	return ;
}