/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:34:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/29 14:54:44 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

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

int	count_char(char *s, char **env, int exit_status)
{
	int n;

	n = 0;
	while (*s)
	{
		if (*s == 39)
		{
			n += count_between_simple(&s);
		}
		else if (*s == 34)
		{
			n += count_between_double(&s, env);
		}
		else if (*s == '$')
		{
			s++;
            n += find_variable(s, env, exit_status);
			s = s + len_var_env(s) - 1;
		}
		else
			n++;
		s++;
	}
	return (n);
}

char *apply_expand(char *res, char *word, char **env)
{
	int i;
	
	i = 0;
    while (*word)
	{
		if (*word == 39)
		{
			i = between_simple(res, &word, i);
		}
		else if (*word == 34)
		{
			i = between_double(res, &word, env, i);
		}
		else if (*word == '$')
		{
			i = out_of_quotes(res, &word, env, i);
			word = word + len_var_env(word) - 1;
		}
		else
			res[i++] = *word;
		word++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_expand(char *word, char **env, int exit_status)
{
	char *res;
	char *trim;
	int len_malloc;

	(void)exit_status;
	if (!word)
		return (NULL); // ERROR
	trim = ft_strtrim(word, " ");
	len_malloc = count_char(trim, env, exit_status);
	res = malloc(sizeof(char) * (len_malloc + 1));
	if (!res)
		return (NULL); // ERROR
	res = apply_expand(res, trim, env);
	free(trim);
	free(word); // commente pour le test dans le main
	return (res);
}
