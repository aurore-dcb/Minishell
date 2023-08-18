/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:37 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/18 12:51:59 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"
#include "../libft/libft.h"

void	builtins_pwd(char **env)
{
	int i;
	int j;

	i = 0;
	j = 4;
	if (!env)
		return ;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PWD=", 4))
		{
			while (env[i][j])
			{
				printf("%c", env[i][j]);
				j++;
			}
			printf("\n");
			return ;
		}
		i++;
	}
}
