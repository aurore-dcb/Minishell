/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:46:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 10:43:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*existing_var(char *var, s_data *data, t_type type)
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
		begin = begin->next;
	}
	free(res);
	return (NULL);
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

int	find_variable_special(char **s, s_data *data, token **token)
{
	int		n;
	char	*cpy;
	char	*res;
	char	*trim;

	trim = NULL;
	if (**s == '?')
		return (size_nb(data->exit_status));
	cpy = malloc(sizeof(char) * (len_var_env(*s) + 1));
	if (!cpy)
		return (0);
	cpy = ft_strcpy(cpy, *s, len_var_env(*s) + 1);
	res = existing_var(cpy, data, (*token)->type);
	if (cpy != NULL)
		free(cpy);
	if (res)
	{
		n = ft_strlen_expand(res);
		if (n != ft_strlen(res))
		{
			trim = ft_trim(res, ft_strlen_expand(res));
			new_words(trim, data, token);
			free(trim);
		}
		free(res);
		return (n);
	}
	return (0);
}

int	find_variable(char *s, s_data *data, token **token)
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

int	count_between_double(char **s, s_data *data, token **token)
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
