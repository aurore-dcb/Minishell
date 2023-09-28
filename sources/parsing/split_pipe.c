/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:23:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:56:23 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	nb_between_quotes(char **str, int i)
{
	char	q;

	i = 0;
	q = *(*str)++;
	i++;
	while (**str && **str != q)
	{
		(*str)++;
		i++;
	}
	(*str)++;
	i++;
	return (i);
}

int	nb_mots_cmd(char *str)
{
	int	mots;
	int	i;

	mots = 1;
	i = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == 34 || *str == 39)
			i = nb_between_quotes(&str, i);
		if (*str && *str == '|')
			mots++;
		if (*str)
		{
			i++;
			str++;
		}
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

void	split2_pipe(char **input, t_cmd_line **cmd)
{
	int			j;
	char		q;
	t_cmd_line	*begin;

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

int	split_pipe(char *input, t_cmd_line **list)
{
	int			n;
	t_cmd_line	*new;

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
