/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:14:55 by aurore            #+#    #+#             */
/*   Updated: 2023/09/13 12:13:14 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_lettre(const char *s, const char sep)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == sep)
			return (i);
		i++;
	}
	return (i);
}

static char	**error(char **res, int i)
{
	while (i < 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

static char	**fill_tab(const char *str, char **tab)
{
	int	j;

	while (*str && *str == '=')
		str++;
	tab[0] = malloc(sizeof(char) * nb_lettre(str, '=') + 1);
	if (!tab[0])
		return (error(tab, 0));
	j = 0;
	while (*str && *str != '=')
		tab[0][j++] = *str++;
	tab[0][j] = '\0';
	str++;
	if (*str == '\0')
	{
		tab[1] = NULL;
		return (tab);
	}
	tab[1] = malloc(sizeof(char) * nb_lettre(str, '\0') + 1);
	if (!tab[1])
		return (error(tab, 1));
	j = 0;
	while (*str)
		tab[1][j++] = *str++;
	tab[1][j] = '\0';
	return (tab);
}

char	**ft_split_env(const char *str)
{
	char	**tab;

	if (str == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * 3);
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(str, tab);
	if (!tab[1])
		tab[1] = 0;
	tab[2] = 0;
	return (tab);
}
