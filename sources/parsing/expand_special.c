/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:27 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/26 15:10:50 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strlen_expand(char *var)
{
	int	i;

	i = 0;
	while (var && var[i] && var[i] != ' ')
		i++;
	return (i);
}

token	*ft_lstnew_token_special(char *var, token *current)
{
	token	*elem;

	elem = malloc(sizeof(token));
	if (!elem)
		return (NULL);
    elem->word = ft_substr(var, 0, ft_strlen_expand(var));
    elem->next = current->next;
    elem->previous = current;
    elem->type = 1; // a changer par la suite 
    current->next = elem;
    return (elem);
}

void	new_words(char *var, s_data *data, token **maillon)
{
	token *new;
    (void)data;
    new = NULL;
    while (*var != '\0')
	{
		if (*var == ' ')
		{
			var++;
            new = ft_lstnew_token_special(var, *maillon);
		}
        var++;
		while (*var && *var != ' ')
			var++;
	}
}
