/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:49:59 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/28 13:45:05 by rmeriau          ###   ########.fr       */
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

int	parse_env(char **env, t_data *data)
{
	t_env	*new;
	t_env	*newex;
	int		i;

	i = 0;
	while (env && env[i])
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
