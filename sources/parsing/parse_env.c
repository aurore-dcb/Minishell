/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:49:59 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/04 14:00:49 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_pwd(t_env	**envp)
{
	t_env	*begin;

	begin = *envp;
	while (begin)
	{
		if (!ft_strncmp(begin->data, "PWD=", 4))
			printf("%s\n", begin->data);
		if (!ft_strncmp(begin->data, "OLDPWD=", 7))
			printf("%s\n", begin->data);
		begin = begin->next;
	}
	return (1);
}

int	find_path_env(t_env **envp)
{
	t_env	*begin;

	begin = *envp;
	while (begin)
	{
		if (!ft_strncmp(begin->data, "PATH=", 5))
			printf("%s\n", begin->data);
		begin = begin->next;
	}
	return (0);
}


t_env	*ft_lstnew_env(char *data)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->data = ft_strdup(data);
	if (!elem->data)
		return (NULL);
	elem->next = NULL;
	return (elem);
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

int    parse_env(char **env, s_data *data)
{
    t_env    *new;
    int        i;

    i = 0;
    if (!env)
        return (0);
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PWD=", 4))
            data->pwd = ft_strdup(env[i]);
        else if (!ft_strncmp(env[i], "OLDPWD=", 7))
            data->oldpwd = ft_strdup(env[i]);
        new = ft_lstnew_env(env[i]);
        if (!new)
            return (0);
        ft_lstadd_back_env(&data->envp, new);
        i++;
    }
    return (1);
}