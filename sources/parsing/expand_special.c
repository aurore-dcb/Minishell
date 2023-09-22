/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:27 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 16:11:45 by aducobu          ###   ########.fr       */
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
	// var est la variable d'env.
	// ex : ' ls -l -a' sans sa premiere partie => var = '-l -a'
	token *new;
    (void)data;
    new = NULL;
    while (*var != '\0')
	{
		if (*var == ' ')
		{
			var++;
			//nouveau maillon a inserer juste apres l'actuel
            new = ft_lstnew_token_special(var, *maillon);
			// printf("new->word = %s\n", new->word);
			// 1 - nouveau maillon
			// 2 - new->next = current->next
			// 3 - new->previous = current
			// 4 - new->type
			// 5 - new->word -> substr de var pour une taille de strlen_expand
			// 3 - current->next = new
		}
        var++;
		while (*var && *var != ' ')
			var++;
	}
	// quitter tout jusqu'a expand pour continuer l'expand a partir des nouveaux maillons
	// le refaire pour le maillon actuel ?
}
