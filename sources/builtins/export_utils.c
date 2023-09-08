/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:17:07 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/08 14:37:07 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_swap(t_env *a, t_env *b)
{
	char	*val_tmp;
	char	*key_tmp;

	val_tmp = a->data;
	a->data = b->data;
	b->data = val_tmp;
	key_tmp = a->key;
	a->key = b->key;
	b->key = key_tmp;
}

t_env	*ft_sort_list(t_env *envex)
{
	t_env	*begin;

	begin = envex;
	while (envex->next)
	{
		if (ft_strcmp(envex->key, envex->next->key) > 0)
		{
			ft_swap(envex, envex->next);
			envex = begin;
		}
		else
			envex = envex->next;
	}
	envex = begin;
	return (envex);
}

void	print_sorted_env(t_env *envex)
{
	t_env	*tmp;
	t_env	*begin;

	begin = envex;
	tmp = ft_sort_list(begin);
	while (tmp)
	{
		if (tmp->data)
			printf("export %s=\"%s\"\n", tmp->key, tmp->data);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	ft_lstreplace_env(t_env **lst, t_env *new)
{
	t_env	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
		{
			if (!ft_strcmp(list->next->key, new->key))
			{
				new->next = list->next->next;
				list->next = new;
			}
			list = list->next;
		}
	}
	else
		*lst = new;
}

void	ft_lstjoin_env(t_env **lst, t_env *new)
{
	t_env	*list;

	list = *lst;
	if (list)
	{
		while (list)
		{
			if (!ft_strcmp(list->key, new->key))
				list->data = ft_strjoin(list->data, new->data);
			list = list->next;
		}
	}
	else
		*lst = new;
}
