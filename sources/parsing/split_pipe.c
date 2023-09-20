/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:23:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/20 14:24:10 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	nb_mots_cmd(char *str)
{
	int		mots;
	char	q;
	int		i;

	mots = 1;
	i = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == 34 || *str == 39)
		{
			q = *str++;
			while (*str && *str != q)
				str++;
			str++;
		}
		if (*str && *str == '|')
			mots++;
		if (*str)
			str++;
	}
	return (mots);
}

int	nb_lettre_cmd(char *s)
{
	int		i;
	char	q;

	i = 0;
	while (s && i < ft_strlen(s))
	{
		if (s[i] == 34 || s[i] == 39)
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			if (s[i] == '\0')
				return (i);
			i++;
		}
		if (s[i] && s[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

void	split2_pipe(char **input, cmd_line **cmd)
{
	int			j;
	char		q;
	cmd_line	*begin;

	j = 0;
	begin = ft_lstlast_cmd_line(*cmd);
	while (*(*input) && *(*input) != '|')
	{
		if (*(*input) == 34 || *(*input) == 39)
		{
			q = *(*input);
			begin->cmd[j++] = *(*input)++;
			while (*(*input) && *(*input) != q)
				begin->cmd[j++] = *(*input)++;
			if (*(*input) == '\0')
				return ;
			begin->cmd[j++] = *(*input)++;
		}
		if (*(*input) && *(*input) != '|')
			begin->cmd[j++] = *(*input)++;
	}
	begin->cmd[j] = '\0';
}

int	split_pipe(char *input, cmd_line **list)
{
	int			n;
	cmd_line	*new;

	if (input == NULL)
		return (0);
	n = nb_mots_cmd(input);
	while (n)
	{
		if (*input == '|')
			input++;
		new = ft_lstnew_cmd_line(nb_lettre_cmd(input) + 1);
		if (!new)
			return (0);
		ft_lstadd_back_cmd_line(list, new);
		split2_pipe(&input, list);
		n--;
	}
	return (split_word(*list));
}
