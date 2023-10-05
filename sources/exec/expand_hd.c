/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:58:47 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 18:35:30 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	quotes_hd(t_token *tok, t_token **token_hd)
{
	char	*tmp;

	tmp = NULL;
	if (tok->word && surr_by_quotes(tok->word))
	{
		tmp = ft_trim_hd(tok->word);
		if (!tmp)
			return (free_token(*token_hd), 0);
		free(tok->word);
		tok->word = ft_strdup(tmp);
		free(tmp);
	}
	return (1);
}

int	make_expand(t_token *tok, t_data *data, t_token *curr, t_token **token_hd)
{
	if (!quotes_hd(tok, token_hd))
		return (0);
	else if (!surr_by_quotes(tok->word))
	{
		if (ft_strchr(curr->word, '$'))
		{
			curr->word = ft_expand(curr->word, data, token_hd, 1);
			if (!curr->word)
				return (free_token(*token_hd), 0);
		}
	}
	return (1);
}

int	expand_here_doc(t_token *tok, t_data *data, char *lign, t_pipex *pipex)
{
	t_token	*curr;
	t_token	*token_hd;

	token_hd = NULL;
	if (!lign || !add_word_hd(&token_hd, lign))
		return (0);
	curr = token_hd;
	while (curr)
	{
		if (!make_expand(tok, data, curr, &token_hd))
			return (free_token(token_hd), 0);
		if ((ft_strcmp(curr->word, tok->word) == 0))
			return (free_token(token_hd), 0);
		ft_putstr_fd(curr->word, pipex->here_doc_file);
		curr = curr->next;
	}
	return (free_token(token_hd), 1);
}
