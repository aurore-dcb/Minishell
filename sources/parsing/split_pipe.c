/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:23:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/23 16:27:32 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	nb_mots_cmd(char *str)
{
	int		mots;
	int		sep;
	char	q;

	mots = 0;
	sep = 1;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			q = *str++;
			while (*str && *str != q)
				str++;
			str++;
		}
		if (*str == '|')
			sep = 1;
		else if (sep == 1)
		{
			mots++;
			sep = 0;
		}
		str++;
	}
	return (mots);
}

int	nb_lettre_cmd(char *s)
{
	int		i;
	char	q;

	i = 0;
	while (s[i])
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
		if (s[i] == '|')
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
		begin->cmd[j++] = *(*input)++;
	}
	begin->cmd[j] = '\0';
}

void	split_pipe(char *input, cmd_line **list)
{
	int			j;
	int			n;

	if (input == NULL)
		return ;
	n = nb_mots_cmd(input);
	while (n)
	{
		if (*input == '|')
			input++;
		ft_lstadd_back_cmd_line(list, ft_lstnew_cmd_line(nb_lettre_cmd(input)
					+ 1));
		j = 0;
		split2_pipe(&input, list);
		n--;
	}
}
