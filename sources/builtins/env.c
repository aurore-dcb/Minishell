/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 13:40:59 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void builtin_env(char **env)
// {
//     int i;

//     i = 0;
// 	if (!env)
// 		return ;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }

void	builtin_env(s_data *data)
{
	t_env	*begin;

	begin = data->envp;
	if (!data->envp)
		return ;
	while (begin)
	{
		if (!ft_strncmp(begin->data, "PWD=", 4))
			printf("%s\n", data->pwd);
		else if (!ft_strncmp(begin->data, "OLDPWD=", 7))
			printf("%s\n", data->oldpwd);
		else
			printf("%s\n", begin->data);
		begin = begin->next;
	}
}