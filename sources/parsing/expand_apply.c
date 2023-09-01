/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:01:12 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 10:32:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int between_simple(char *res, char **word, int i)
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

int out_of_quotes(char *res, char **word, s_data *data, int i)
{
	int j;
	char *cpy;
	char *var;

	j = 0;
	(*word)++;
	cpy = malloc(sizeof(char) * (len_var_env(*word) + 1));
	if (!cpy)
		return (printf("echec malloc\n"), 0);
	cpy = ft_strcpy(cpy, *word, len_var_env(*word) + 1);
	if (**word == '?')
        var = ft_itoa(data->exit_status);
    else
        var = existing_var(cpy, data);
    while (var && var[j])
        res[i++] = var[j++];
    return (i);	
}

int between_double(char *res, char **word, s_data *data, int i)
{
    (*word)++;
    while (*(*word) && *(*word) != 34)
    {
        if (*(*word) == '$')
        {
            i = out_of_quotes(res, word, data, i);
            (*word) = (*word) + len_var_env(*word) - 1;
        }
        else
            res[i++] = *(*word);
        (*word)++;
    }
    return (i);
}
