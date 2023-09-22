/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:46:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 11:42:35 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*existing_var(char *var, s_data *data)
{
	t_env	*begin;
	char	*res;

	begin = data->envp;
	if (!var)
		return (NULL);
	while (begin)
	{
		if (ft_strnstr(begin->key, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(begin->key))
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

int	find_variable_special(char *s, s_data *data, token **token)
{
	int		n;
	char	*cpy;
	char	*res;

	if (*s == '?')
		return (size_nb(data->exit_status));
	cpy = malloc(sizeof(char) * (len_var_env(s) + 1));
	if (!cpy)
		return (0);
	cpy = ft_strcpy(cpy, s, len_var_env(s) + 1);
	res = existing_var(cpy, data);
	// expand special
	if (res)
	{
		n = ft_strlen_expand(res);
		printf("ft_strlen_expand = %d\n", n);
		if (n != ft_strlen(res)) // il y a au moins un espace dans la variable d'env donc au moins un maillon a creer -> faire une boucle pour les maillons
		{
			res = ft_trim(res, ft_strlen_expand(res)); // on enleve la premiere partie du mot / de la variable
			printf("res = %s\n", res);
			new_words(res, data, token); // on cree les nouveaux maillons avec la/les autres parties de la varible
			// return (-1);
		}
		free(res);
		return (n);
	}
	return (0);
}

int	find_variable(char *s, s_data *data)
{
	int		n;
	char	*cpy;
	char	*res;

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

int	count_between_double(char **s, s_data *data)
{
	int	n;

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
