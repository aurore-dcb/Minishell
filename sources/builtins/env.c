/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 14:52:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_env(t_data *data)
{
	t_env	*begin;

	begin = data->envp;
	if (!data->envp)
	{
		g_exit = 1;
		return (EXIT_FAILURE);
	}
	while (begin)
	{
		if (begin->key)
			printf("%s=", begin->key);
		if (begin->data)
			printf("%s", begin->data);
		printf("\n");
		begin = begin->next;
	}
	g_exit = 0;
	return (EXIT_SUCCESS);
}
