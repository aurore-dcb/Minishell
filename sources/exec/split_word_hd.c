/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:39:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 16:59:54 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	get_type_hd(t_token *lst)
{
	if (lst && lst->next)
	{
		lst = lst->next;
		while (lst)
		{
			if (lst->previous->type == FILE_IN && lst->type == ARG)
				lst->type = OPEN_FILE;
			else if (lst->previous->type == HERE_DOC && lst->type == ARG)
				lst->type = LIMITOR;
			else if (lst->previous->type == FILE_OUT && lst->type == ARG)
				lst->type = EXIT_FILE;
			else if (lst->previous->type == FILE_OUT_SUR && lst->type == ARG)
				lst->type = EXIT_FILE_RET;
			lst = lst->next;
		}
	}
}

t_token	*ft_lstnew_token_hd(char *lign, int start, int end)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!elem->word)
		return (NULL);
	ft_strcpy_pos(elem->word, lign, start, end);
	elem->type = get_type_meta(elem->word);
	elem->next = NULL;
	elem->previous = NULL;
	return (elem);
}

int	add_word_hd(t_token **token_hd, char *lign)
{
	t_token	*new;

	new = NULL;
	new = ft_lstnew_token_hd(lign, 0, ft_strlen(lign));
	if (!new)
		return (0);
	ft_lstadd_back_token(token_hd, new);
	get_type_hd(*token_hd);
	return (1);
}

int	surr_by_quotes(char *s)
{
	int	start;
	int	end;

	if (!s)
		return (0);
	start = 0;
	end = ft_strlen(s);
	if (start != end)
	{
		if (s[start] == 39 && s[end - 1] == 39)
			return (1);
		else if (s[start] == 34 && s[end - 1] == 34)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*ft_trim_hd(char const *s1)
{
	char	*ret;
	char	*start;
	char	*end;
	int		c;

	if (!s1)
		return (0);
	c = s1[0];
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && *start == c)
		++start;
	while (start < end && *(end - 1) == c)
		--end;
	ret = ft_substr(start, 0, end - start);
	return (ret);
}
