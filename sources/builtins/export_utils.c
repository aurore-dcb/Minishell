/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:17:07 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/19 10:28:22 by aducobu          ###   ########.fr       */
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
	t_env	*prev;

	list = *lst;
	prev = NULL;
	if (list)
	{
		while (list)
		{
			if (!ft_strcmp(list->key, new->key))
			{
				if (prev)
					prev->next = new;
				else
					*lst = new;
				new->next = list->next;
				free_elem_env(list);
				return ;
			}
			prev = list;
			list = list->next;
		}
	}
	else
		*lst = new;
}

void	ft_lstjoin_env(t_env **lst, t_env *new)
{
	t_env	*list;
	char	*tmp;

	list = *lst;
	if (list)
	{
		while (list)
		{
			if (!ft_strcmp(list->key, new->key))
			{	
				tmp = ft_strdup(list->data);
				free(list->data);
				list->data = ft_strjoin(tmp, new->data);
				free(tmp);
			}
			list = list->next;
		}
	}
	else
		*lst = new;
}
