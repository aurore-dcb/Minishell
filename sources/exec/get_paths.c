/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:32:42 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 10:31:35 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_trim_pipex(char *s)
{
	int		i;
	char	*res;

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
	// int		i;
	char	*lign;
	char	**paths;
    t_env *begin;

	// i = 0;
    begin = *envp;
	if (!begin)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->data, "PATH=", 5))
		{
			lign = ft_trim_pipex(begin->data);
			if (!lign)
				return (0);
			paths = ft_split(lign, ':');
			free(lign);
			return (paths);
		}
        begin = begin->next;
		// i++;
	}
	return (NULL);
}

// char	*find_path(char **paths, char *cmd)
// {
// 	int		i;
// 	char	*slash;
// 	char	*all_path;

// 	i = -1;
// 	if (!cmd)
// 		return (NULL);
// 	while (paths[++i])
// 	{
// 		if (access(cmd, F_OK | R_OK | X_OK) == 0)
// 			return (ft_substr(cmd, 0, ft_strlen(cmd)));
// 		slash = ft_strjoin(paths[i], "/");
// 		if (!slash)
// 			return (NULL);
// 		all_path = ft_strjoin(slash, cmd);
// 		free(slash);
// 		if (!all_path)
// 			return (NULL);
// 		if (access(all_path, F_OK | R_OK | X_OK) == 0)
// 			return (all_path);
// 		free(all_path);
// 	}
// 	return (NULL);
// }
