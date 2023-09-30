/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurore <aurore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:39:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/30 09:50:43 by aurore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	get_type_hd(t_token *lst)
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

void free_token(t_token *token)
{
	t_token		*cur_token;
	
	cur_token = NULL;
	while (token)
	{
		cur_token = token;
		token = token->next;
		if (cur_token->word != NULL)
			free(cur_token->word);
		free(cur_token);
	}
}

int	add_word_hd(t_token **token_hd, char *lign)
{
	int		i;
	int		start;
	t_token	*new;

	i = 0;
	start = 0;
	new = NULL;
	while (lign[i])
	{
		while (is_spaces(lign[i]) && lign[i])
			i++;
		start = i;
		i = get_end_word(lign, i);
		new = ft_lstnew_token_hd(lign, start, i);
		if (!new)
			return (0);
		ft_lstadd_back_token(token_hd, new);
	}
	get_type(token_hd);
	free_token(*token_hd);
	return (1);
}

// int	split_word_hd(t_token *token_hd)
// {
// 	while (list)
// 	{
// 		if (!list->cmd[0])
// 			return (0);
// 		add_word(list);
// 		list = list->next;
// 	}
// 	return (1);
// }
