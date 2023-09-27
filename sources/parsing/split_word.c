/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:40:16 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/27 14:38:16 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_strcpy_pos(char *dst, char *src, int start, int end)
{
	int	i;

	i = 0;
	while (src[start] && start < end)
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
}

t_type	get_type_meta(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (len == 1)
	{
		if (word[0] == '>')
			return (FILE_OUT);
		else if (word[0] == '<')
			return (FILE_IN);
	}
	else if (len == 2)
	{
		if (word[0] == '>' && word[1] == '>')
			return (FILE_OUT_SUR);
		else if (word[0] == '<' && word[1] == '<')
			return (HERE_DOC);
	}
	if (len > 0)
		return (ARG);
	return (NONE);
}

void	get_type(token *lst)
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

int	add_word(cmd_line *list)
{
	int		i;
	int		start;
	token	*new;

	i = 0;
	start = 0;
	list->token = NULL;
	while (list->cmd[i])
	{
		while (is_spaces(list->cmd[i]) && list->cmd[i])
			i++;
		start = i;
		i = get_end_word(list->cmd, i);
		new = ft_lstnew_token(list, start, i);
		if (!new)
			return (0);
		ft_lstadd_back_token(&list->token, new);
	}
	get_type(list->token);
	return (1);
}

int	split_word(cmd_line *list)
{
	while (list)
	{
		if (!list->cmd[0])
			return (0);
		add_word(list);
		list = list->next;
	}
	return (1);
}
