/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:34:24 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/25 15:29:02 by aducobu          ###   ########.fr       */
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

int len_var_env(char *s)
{
	int len;

	len = 0;
	while (*s && (*s == '_' || ft_isalnum(*s)))
	{
		len++;
		s++;
	}
	return (len);
}

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

char *existing_var(char *var, char **env)
{
	int i;
	char *res;
	
	i = 0;
	if (!var)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], var, ft_strlen(var)))
		{
			res = ft_trim(env[i], ft_strlen(var) + 1);
			if (!res)
				return (free(var), NULL);
			return (free(var), res);
		}
		i++;
	}
	free(var);
	return (NULL);
}

int between_double(char **s, char **env)
{
	int n;
	char *cpy;
	char *res;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 34)
	{
		if (*(*s) == '$')
		{
			(*s)++;
			cpy = malloc(sizeof(char)  * (len_var_env(*s) + 1));
			if (!cpy)
				return (printf("echec malloc\n"), 0); // ERREUR
			cpy = ft_strcpy(cpy, *s, len_var_env(*s) + 1);
			res = existing_var(cpy, env);
			n += ft_strlen(res);
			printf("n = %d\n", n);
			(*s) = (*s) + len_var_env(*s) - 1;
			// printf("res = %s\n", res);
		}
		else
		{
			printf("char = .%c.\n", *(*s));
			n++;
			printf("n char seul entre double = %d\n", n);
		}
		(*s)++;
	}
	// printf("n = %d\n", n);
	return (n);
}

int	count_char(char *s, char **env)
{
	int n;
	char *cpy;
	char *res;

	n = 0;
	while (*s)
	{
		if (*s == 39) // '
		{
			n += between_simple(&s);
			printf("entre simple N = %d\n", n);
		}
		else if (*s == 34) // "
		{
			n += between_double(&s, env);
			printf("entre double N = %d\n", n);
		}
		else if (*s == '$')
		{
			s++;
			cpy = malloc(sizeof(char)  * (len_var_env(s) + 1));
			if (!cpy)
				return (printf("echec malloc\n"), 0); // ERREUR
			cpy = ft_strcpy(cpy, s, len_var_env(s) + 1);
			res = existing_var(cpy, env);
			n += ft_strlen(res);
			s = s + len_var_env(s);
			printf("apres $ dehors n = %d\n", n);
			// printf("res = %s\n", res);
		}
		else
		{
			n++;
			printf("n char seul = %d\n", n);
		}
		s++;
	}
	return (n);
}

char	*ft_expand(char *word, char **env)
{
	// char *res;
	char *trim;

	if (!word)
		return (NULL);
	trim = ft_strtrim(word, " ");
	printf("count_char = %d\n", count_char(word, env));
	// free(word);
	return (trim);
	// return (res);
}