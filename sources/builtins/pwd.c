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

void	builtin_pwd(s_data *data)
{
	t_env	*tmp;

	if (!data->envp)
		return ;
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return ;
}