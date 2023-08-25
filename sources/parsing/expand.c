/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:34:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/25 14:00:34 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int between_simple(char **s)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 39)
	{
		n++;
		(*s)++;
	}
	printf("n = %d\n", n);
	return (n);
}

int between_double(char **s)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 34)
	{
		if (*(*s) == '$')
		{
			(*s)++;
			// while (*(*s) && *(*s) == '_' || ft_isalnum(*(*s)))
			// {
			// 	n++;
			// 	(*s)++;
			// }
		}
		n++;
		(*s)++;
	}
	printf("n = %d\n", n);
	return (n);
}

int	count_char(char *s)
{
	int n;

	n = 0;
	while (*s)
	{
		if (*s == 39) // '
		{
			n += between_simple(&s);
		}
		else if (*s == 34) // "
		{
			n += between_double(&s)
		}
		s++;
	}
	return (n);
}

char	*ft_expand(char *word)
{
	// char *res;
	char *trim;

	if (!word)
		return (NULL);
	trim = ft_strtrim(word, " ");
	printf("count_char = %d\n", count_char(word));
	// free(word);
	return (trim);
	// return (res);
}