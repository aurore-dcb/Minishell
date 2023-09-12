/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:49:59 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/12 17:16:39 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	copy_elem(char **split_res, char *nul_char, t_env *elem)
{
	if (split_res[0])
	{
		elem->key = ft_strdup(split_res[0]);
		if (!elem->key)
			return (0);
	}
	else
		elem->key = NULL;
	if (split_res[1] && split_res[1][0] != '\0')
	{
		elem->data = ft_strdup(split_res[1]);
		if (!elem->data)
			return (0);
	}
	else
		elem->data = nul_char;
	return (1);
}

// t_env	*ft_lstnew_env(char *data)
// {
// 	t_env	*elem;
// 	char	**split_res;

// 	elem = malloc(sizeof(t_env));
// 	if (!elem)
// 		return (NULL);
// 	split_res = ft_split_env(data);
// 	if (!split_res)
// 		return (NULL);
// 	if (!copy_elem(split_res, NULL, elem))
// 		return (NULL);
// 	elem->next = NULL;
// 	return (elem);
// }

// t_env	*ft_lstnew_env_equal(char *data)
// {
// 	t_env	*elem;
// 	char	**split_res;

// 	elem = malloc(sizeof(t_env));
// 	if (!elem)
// 		return (NULL);
// 	split_res = ft_split_env(data);
// 	if (!split_res)
// 		return (NULL);
// 	if (!copy_elem(split_res, "", elem))
// 		return (NULL);
// 	elem->next = NULL;
// 	return (elem);
// }

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*lst = new;
}

int	parse_env(char **env, s_data *data)
{
	t_env	*new;
	t_env	*newex;
	int		i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		new = ft_lstnew_env(env[i]);
		if (!new)
			return (0);
		newex = ft_lstnew_env(env[i]);
		if (!newex)
			return (free(new), 0);
		ft_lstadd_back_env(&data->envp, new);
		ft_lstadd_back_env(&data->envex, newex);
		i++;
	}
	return (1);
}
