/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:24:56 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/22 15:00:21 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"
#include "../libft/libft.h"

int	is_meta(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	nb_mots(char *str, char c)
{
    (void)c;
	int	mots;
	int	sep;

	mots = 0;
	sep = 1;
	while (*str)
	{
        if (is_meta(*str))
			sep = 1;
		else if (sep == 1)
		{
			mots++;
			sep = 0;
		}
		str++;
	}
	return (mots);
}

int	nb_lettre(char *s, char c)
{
    (void)c;
	int	i;

	i = 0;
    while(s[i] && !is_meta(s[i]))
		i++;
	return (i);
}

char	**error(char **res, int i)
{
	while (i < 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

char	**split_meta(char *input, char c)
{
	char **tab;
	int i;
	int j;

	if (input == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (nb_mots(input, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (nb_mots(input, c))
	{
        while (*input && is_meta(*input))
			input++;
		tab[i] = malloc(sizeof(char) * nb_lettre(input, c) + 1);
		if (!tab[i])
			return (error(tab, i));
		j = 0;
        while (*input && !is_meta(*input))
			tab[i][j++] = *input++;
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
