/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:29:40 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/12 16:57:48 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*ft_lstnew_env(char *data)
{
	t_env	*elem;
	char	**split_res;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	split_res = ft_split_env(data);
	if (!split_res)
		return (NULL);
	if (!copy_elem(split_res, NULL, elem))
		return (NULL);
	elem->next = NULL;
	free_tab(split_res);
	return (elem);
}

t_env	*ft_lstnew_env_no_equal(char *data)
{
	t_env	*elem;
	char	**split_res;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	split_res = malloc(sizeof(char *) * 3);
	if (!split_res)
		return (NULL);
	split_res[0] = ft_strdup(data);
	split_res[1] = NULL;
	split_res[2] = NULL;
	if (!copy_elem(split_res, NULL, elem))
		return (NULL);
	elem->next = NULL;
	free_tab(split_res);
	return (elem);
}

t_env	*ft_lstnew_env_equal(char *data)
{
	t_env	*elem;
	char	**split_res;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	split_res = ft_split_env(data);
	if (!split_res)
		return (NULL);
	if (!copy_elem(split_res, "", elem))
		return (NULL);
	elem->next = NULL;
	free_tab(split_res);
	return (elem);
}
