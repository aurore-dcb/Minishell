/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:27 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/02 10:46:40 by aducobu          ###   ########.fr       */
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

int	do_find(t_token **token, char *res, char *trim)
{
	int	n;

	n = ft_strlen_expand(res);
	if (n != ft_strlen(res))
	{
		trim = ft_trim(res, ft_strlen_expand(res));
		new_words(trim, token);
		free(trim);
	}
	free(res);
	return (n);
}

int	find_variable_special(char **s, t_data *data, t_token **token)
{
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
		return (do_find(token, res, trim));
	return (0);
}

t_token	*ft_lstnew_token_special(char *var, t_token *current)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->word = ft_substr(var, 0, ft_strlen_expand(var));
	elem->next = current->next;
	elem->previous = current;
	elem->type = 1;
	current->next = elem;
	return (elem);
}

void	new_words(char *var, t_token **link)
{
	t_token	*curr;

	curr = *link;
	while (*var && *var != '\0')
	{
		if (*var == ' ')
		{
			var++;
			ft_lstnew_token_special(var, curr);
			curr = curr->next;
		}
		var++;
		while (*var && *var != ' ')
			var++;
	}
}
