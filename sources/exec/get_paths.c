/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:32:42 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/06 10:37:54 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**get_paths(t_env **envp)
{
	char	**paths;
	t_env	*begin;

	begin = *envp;
	if (!begin)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->key, "PATH", 4))
		{
			if (!begin->data)
				return (NULL);
			paths = ft_split(begin->data, ':');
			if (paths == NULL)
				return (0);
			return (paths);
		}
		begin = begin->next;
	}
	return (NULL);
}
