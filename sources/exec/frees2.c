/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:23:18 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/26 10:25:10 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_elem_env(t_env *list)
{
	if (list->data && ft_strcmp(list->data, "") != 0)
		free(list->data);
	if (list->key)
		free(list->key);
	if (list)
		free(list);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free_elem_env(temp);
	}
}
