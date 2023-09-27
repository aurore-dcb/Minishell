/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:01:12 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 08:40:36 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	between_simple(char *res, char **word, int i)
{
	(*word)++;
	while (*(*word) && *(*word) != 39)
	{
		res[i] = *(*word);
		(*word)++;
		i++;
	}
	return (i);
}

int	out_of_quotes(char *res, char **word, s_data *data, int i)
{
	int		j;
	char	*cpy;
	char	*var;

	j = 0;
	(*word)++;
	var = NULL;
	cpy = malloc(sizeof(char) * (len_var_env(*word) + 1));
	if (!cpy)
		return (0);
	cpy = ft_strcpy(cpy, *word, len_var_env(*word) + 1);
	if (**word == '?')
		var = ft_itoa(data->exit_status);
	else
		var = existing_var(cpy, data, 1);
	if (ft_strlen_expand(var) != ft_strlen(var))
		while (var && var[j] != ' ')
			res[i++] = var[j++];
	else
		while (var && var[j])
			res[i++] = var[j++];
	if (cpy != NULL)
		free(cpy);
	free(var);
	return (i);
}

int apply_out_quotes(char *res, char **word, s_data *data, int i)
{
	int j;
	char *cpy;
	char *var;

	j = 0;
	(*word)++;
	cpy = malloc(sizeof(char) * (len_var_env(*word) + 1));
	if (!cpy)
		return (0);
	cpy = ft_strcpy(cpy, *word, len_var_env(*word) + 1);
	if (**word == '?')
        var = ft_itoa(data->exit_status);
    else
        var = existing_var(cpy, data, 1);
    while (var && var[j])
        res[i++] = var[j++];
    free(var);
	free(cpy);
    return (i);	
}

int	between_double(char *res, char **word, s_data *data, int i)
{
	(*word)++;
	while (*(*word) && *(*word) != 34)
	{
		if (**word == '$' && *(*word + 1) && *(*word + 1) != 34 && *(*word + 1) != ' ' && *(*word + 1) != '/')
		{
			i = apply_out_quotes(res, word, data, i);
			(*word) = (*word) + len_var_env(*word) - 1;			
		}
		else
			res[i++] = *(*word);
		(*word)++;
	}
	return (i);
}
