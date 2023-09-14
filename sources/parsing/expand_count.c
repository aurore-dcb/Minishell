/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:46:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/14 10:30:04 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char *existing_var(char *var, s_data *data)
{
	t_env *begin;
	char *res;
	
	begin = data->envp;
	if (!var)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->key, var, ft_strlen(var)))
		{
			res = ft_strdup(begin->data);
			if (!res)
				return (free(var), NULL);
			return (free(var), res);
		}
		begin = begin->next;
	}
	return (NULL);
}

int len_var_env(char *s)
{
	int len;

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

int count_between_simple(char **s)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 39)
	{
		n++;
		(*s)++;
	}
	return (n);
}
int find_variable(char *s, s_data *data)
{
    int n;
    char *cpy;
    char *res;

	if (*s == '?')
		return (size_nb(data->exit_status));
    cpy = malloc(sizeof(char) * (len_var_env(s) + 1));
	if (!cpy)
		return (printf("echec malloc\n"), 0); // ERREUR
    cpy = ft_strcpy(cpy, s, len_var_env(s) + 1);
    res = existing_var(cpy, data);
	n = ft_strlen(res);
	free(res);
    return (n);
}

int count_between_double(char **s, s_data *data)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 34)
	{
		if (*(*s) == '$')
		{
			(*s)++;
            n += find_variable(*s, data);
			(*s) = (*s) + len_var_env(*s) - 1;
		}
		else
			n++;
		(*s)++;
	}
	return (n);
}
