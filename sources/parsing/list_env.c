/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:29:40 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/02 16:41:00 by rmeriau          ###   ########.fr       */
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
	if (data)
		split_res[0] = ft_strdup(data);
	else
		split_res[0] = NULL;
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

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	len_var_env(char *s)
{
	int	len;

	len = 0;
	if (*s == '?')
		return (1);
	while (*s && (*s == '_' || ft_isalnum(*s)))
	{
		len++;
		s++;
	}
	return (len);
}
