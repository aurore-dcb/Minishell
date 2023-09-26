/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:32:42 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/26 10:25:32 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_trim_pipex(char *s)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	while (*s && i < 5)
	{
		++s;
		i++;
	}
	res = ft_substr(s, 0, ft_strlen(s) - 5);
	return (res);
}

char	**get_paths(t_env **envp)
{
	char	*lign;
	char	**paths;
	t_env	*begin;

	begin = *envp;
	if (!begin)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->key, "PATH", 4))
		{
			lign = ft_trim_pipex(begin->data);
			if (!lign)
				return (0);
			paths = ft_split(lign, ':');
			free(lign);
			return (paths);
		}
		begin = begin->next;
	}
	return (NULL);
}
