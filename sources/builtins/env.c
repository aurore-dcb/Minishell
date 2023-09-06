/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:55:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 14:26:34 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	builtin_env(s_data *data)
{
	t_env	*begin;

	begin = data->envp;
	if (!data->envp)
		return ;
	while (begin)
	{
		if (begin->key)
			printf("%s=", begin->key);
		if (begin->data)
			printf("%s", begin->data);
		printf("\n");
		begin = begin->next;
	}
}