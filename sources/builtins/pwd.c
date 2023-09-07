/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:37 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/07 15:18:13 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_pwd(s_data *data)
{
	t_env	*tmp;

	if (!data->envp)
		return (EXIT_FAILURE);
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
