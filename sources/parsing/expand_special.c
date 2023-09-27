/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:27 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 10:43:23 by aducobu          ###   ########.fr       */
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
    elem->type = 1;
    current->next = elem;
    return (elem);
}

void	new_words(char *var, s_data *data, token **maillon)
{
	token *new;
	token *curr;
    (void)data;
    new = NULL;
	curr = *maillon;
    while (*var && *var != '\0')
	{
		if (*var == ' ')
		{
			var++;
            new = ft_lstnew_token_special(var, curr);
			curr = curr->next;
		}
        var++;
		while (*var && *var != ' ')
			var++;
	}
}
