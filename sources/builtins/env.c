/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/14 14:04:34 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_env(s_data *data)
{
	t_env	*begin;

	begin = data->envp;
	if (!data->envp)
		return (EXIT_FAILURE);
	while (begin)
	{
		if (begin->key)
			printf("%s=", begin->key);
		if (begin->data)
			printf("%s", begin->data);
		printf("\n");
		begin = begin->next;
	}
	return (EXIT_SUCCESS);
}
