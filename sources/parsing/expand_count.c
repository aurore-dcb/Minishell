/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:46:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:30:32 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_copy(t_env *begin, t_type type, char *var)
{
	char	*res;

	res = NULL;
	if (begin->data && ft_strcmp(begin->data, "") != 0)
	{
		if (type == LIMITOR)
		{
			res = ft_strdup(var);
			return (res);
		}
		res = ft_strdup(begin->data);
		if (!res)
			return (NULL);
	}
	else
		res = ft_strdup("");
	return (res);
}

char	*existing_var(char *var, t_data *data, t_type type)
{
	t_env	*begin;
	char	*res;

	res = NULL;
	begin = data->envp;
	if (!var)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->key, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(begin->key))
		{
			res = ft_copy(begin, type, var);
			return (res);
		}
		begin = begin->next;
	}
	free(res);
	return (NULL);
}

int	count_between_simple(char **s)
{
	int	n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 39)
	{
		n++;
		(*s)++;
	}
	return (n);
}

int	find_variable(char *s, t_data *data, t_token **token)
{
	int		n;
	char	*cpy;
	char	*res;

	if (*s == '?')
		return (size_nb(data->exit_status));
	cpy = malloc(sizeof(char) * (len_var_env(s) + 1));
	if (!cpy || len_var_env(s) == 0)
		return (free(cpy), 0);
	cpy = ft_strcpy(cpy, s, len_var_env(s) + 1);
	res = existing_var(cpy, data, (*token)->type);
	n = ft_strlen(res);
	free(cpy);
	free(res);
	return (n);
}

int	count_between_double(char **s, t_data *data, t_token **token)
{
	int	n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 34)
	{
		if (**s == '$' && *(*s + 1) && *(*s + 1) != 34 && *(*s + 1) != ' '
			&& *(*s + 1) != '/')
		{
			(*s)++;
			n += find_variable(*s, data, token);
			(*s) = (*s) + len_var_env(*s) - 1;
		}
		else
			n++;
		(*s)++;
	}
	return (n);
}
