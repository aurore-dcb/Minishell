/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:46:02 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/12 16:54:33 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_inv(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '^' || str[0] == '=' || str[0] == '-')
			return (1);
		if (str[i] == '+' || str[i] == '=' || str[i] == '_' || (str[i] >= 'A'
				&& 'z' >= str[i]) || (str[i] >= '0' && '9' >= str[i]))
		{
			if (str[i] == '+')
			{
				if (str[i + 1] == '=')
					return (2);
				return (1);
			}
			else if (str[i] == '=')
				return (0);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	has_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	in_env(t_env *env, char *key)
{
	t_env	*begin;

	begin = env;
	while (begin)
	{
		if (!ft_strcmp(key, begin->key))
			return (1);
		begin = begin->next;
	}
	return (0);
}

void	del_plus(char *str, char to_del)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == to_del)
		str[len - 1] = '\0';
}
