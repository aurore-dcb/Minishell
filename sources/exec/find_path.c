/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:52:48 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 13:59:25 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_trim_paths(char *s)
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

// char	**get_paths(char **env)
// {
// 	int		i;
// 	char	*lign;
// 	char	**paths;

// 	i = 0;
// 	if (!env)
// 		return (NULL);
// 	while (env[i])
// 	{
// 		if (ft_strnstr(env[i], "PATH=", 5))
// 		{
// 			lign = ft_trim_paths(env[i]);
// 			if (!lign)
// 				return (0);
// 			paths = ft_split(lign, ':');
// 			free(lign);
// 			return (paths);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*slash;
	char	*all_path;

	i = -1;
	if (!cmd)
		return (NULL);
	while (paths[++i])
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (ft_substr(cmd, 0, ft_strlen(cmd)));
		slash = ft_strjoin(paths[i], "/");
		if (!slash)
			return (NULL);
		all_path = ft_strjoin(slash, cmd);
		free(slash);
		if (!all_path)
			return (NULL);
		if (access(all_path, F_OK | R_OK | X_OK) == 0)
			return (all_path);
		free(all_path);
	}
	return (NULL);
}
