/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:39:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/02 10:48:46 by aducobu          ###   ########.fr       */
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
	get_type_hd(*token_hd);
	return (1);
}

int	expand_here_doc(t_token **token_hd, t_data *data, char *lign,
		t_pipex *pipex)
{
	t_token	*curr;

	curr = NULL;
	if (!add_word_hd(token_hd, lign))
		return (0);
	curr = *token_hd;
	while (curr)
	{
		curr->word = ft_expand(curr->word, data, token_hd);
		if (!curr->word)
			return (0);
		ft_putstr_fd(curr->word, pipex->here_doc_file);
		if (curr->next)
			ft_putstr_fd(" ", pipex->here_doc_file);
		curr = curr->next;
	}
	return (1);
}
