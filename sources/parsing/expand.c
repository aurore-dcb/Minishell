/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:34:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 13:11:31 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strcpy(char *dst, char *src, int dstsize)
{
	int	i;

	i = 0;
	while (src[i] && i < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (dst);
}

char	*ft_trim(char *s, int len)
{
	int		i;
	char	*res;

	i = 0;
	while (*s && i < len)
	{
		++s;
		i++;
	}
	res = ft_substr(s, 0, ft_strlen(s));
	return (res);
}

int	count_char(char *s, s_data *data, token **token)
{
	int	n;
	int k;

	n = 0;
	while (s && *s != '\0')
	{
		if (*s == 39)
			n += count_between_simple(&s);
		else if (*s == 34)
			n += count_between_double(&s, data);
		else if (*s == '$')
		{
			s++;
			k = find_variable_special(s, data, token);
			n += k;
			if (*s == '?')
				s += len_var_env(s);
			else
				s = s + k;
				// s = s + len_var_env(s) - 1;
		}
		else
			n++;
		if (*s)
			s++;
		// printf("s = %s\n", s);
	}
	return (n);
}

char	*apply_expand(char *res, char *word, s_data *data)
{
	int	i;

	i = 0;
	while (*word)
	{
		if (*word == 39)
			i = between_simple(res, &word, i);
		else if (*word == 34)
			i = between_double(res, &word, data, i);
		else if (*word == '$')
		{
			i = out_of_quotes(res, &word, data, i);
			word = word + len_var_env(word) - 1;
		}
		else
			res[i++] = *word;
		word++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_expand(char *word, s_data *data, token **token)
{
	char	*res;
	char	*trim;
	int		len_malloc;

	if (!word)
		return (NULL);
	trim = ft_strtrim(word, " ");
	len_malloc = count_char(trim, data, token);
	dprintf(1, "len_malloc = %d\n", len_malloc);
	// if (len_malloc == -1)
	// 	return (NULL); // a voir ...
	res = malloc(sizeof(char) * (len_malloc + 1));
	if (!res)
		return (free(trim), NULL);
	res = apply_expand(res, trim, data);
	printf("res = %s\n", res);
	free(trim);
	free(word);
	return (res);
}
