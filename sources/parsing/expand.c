/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:34:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/02 11:26:47 by aducobu          ###   ########.fr       */
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

int	count_char(char *s, t_data *data, t_token **token, int k)
{
	int	n;

	n = 0;
	while (s && *s != '\0')
	{
		if (*s == 39)
			n += count_between_simple(&s);
		else if (*s == 34)
			n += count_between_double(&s, data, token);
		if (*s == '$' && *(s + 1) && *(s + 1) != 34 && *(s + 1) != ' ' && *(s
				+ 1) != '/')
		{
			s++;
			k = find_variable_special(&s, data, token);
			n += k;
			if (*s == '?')
				s += len_var_env(s);
			else if (k == 0)
				s--;
		}
		else
			n++;
		s++;
	}
	return (n);
}

char	*apply_expand(char *res, char *word, t_data *data, t_token **token)
{
	int	i;

	i = 0;
	while (*word)
	{
		if (*word == 39)
			i = between_simple(res, &word, i);
		else if (*word == 34 && (*token)->type != LIMITOR)
			i = between_double(res, &word, data, i);
		else if (*word == '$' && *(word + 1) && *(word + 1) != ' ' && *(word
				+ 1) != '/' && (*token)->type != LIMITOR)
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

char	*trim_isspace(char const *s1, char const *set)
{
	char	*ret;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && ((*start >= 9 && *start <= 13) || *start == 32))
		++start;
	while (start < end && ((*(end - 1) >= 9 && *(end - 1) <= 13) || *(end
				- 1) == 32))
		--end;
	ret = ft_substr(start, 0, end - start);
	return (ret);
}

char	*ft_expand(char *word, t_data *data, t_token **token)
{
	char	*res;
	char	*trim;
	int		len_malloc;

	if (!word)
		return (NULL);
	trim = trim_isspace(word, " ");
	if (!trim)
		return (NULL);
	len_malloc = count_char(trim, data, token, 0);
	res = malloc(sizeof(char) * (len_malloc + 1));
	if (!res)
		return (free(trim), NULL);
	res = apply_expand(res, trim, data, token);
	free(trim);
	free(word);
	return (res);
}
