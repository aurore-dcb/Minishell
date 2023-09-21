/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/21 12:06:11 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_env(s_data *data)
{
	t_env	*begin;

	begin = data->envp;
	if (!data->envp)
	{
		data->exit_status = 1;
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
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
