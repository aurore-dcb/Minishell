/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/18 13:00:45 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"
#include "../libft/libft.h"

void builtin_env(char **env)
{
    int i;

    i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
