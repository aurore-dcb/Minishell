/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:40:24 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/02 16:38:43 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	nb_arg(t_cmd_line *list)
{
	t_token	*cur;
	int		len;

	len = 0;
	cur = list->token;
	while (cur)
	{
		if (cur->type == ARG)
			len++;
		cur = cur->next;
	}
	return (len);
}

void	fill_arg(t_cmd_line *list)
{
	int		i;
	t_token	*cur;

	cur = list->token;
	i = 0;
	while (cur)
	{
		if (cur->type == ARG)
		{
			if (cur->word)
				list->args[i] = ft_strdup(cur->word);
			else
				list->args[i] = NULL;
			i++;
		}
		cur = cur->next;
	}
	list->args[i] = NULL;
}

int	tab_cmd(t_cmd_line **list)
{
	char		**cmd;
	t_cmd_line	*begin;

	begin = *list;
	while (begin)
	{
		cmd = malloc(sizeof(char *) * (nb_arg(begin) + 1));
		if (!cmd)
			return (0);
		begin->args = cmd;
		fill_arg(begin);
		begin = begin->next;
	}
	return (1);
}

char	**new_tab(char **old_tab, int old_len)
{
	int		i;
	char	**new_tab;

	new_tab = (char **)malloc(old_len * sizeof(char *));
	if (!new_tab)
		return (0);
	i = 1;
	while (i < old_len)
	{
		new_tab[i - 1] = ft_strdup(old_tab[i]);
		if (!new_tab[i - 1])
			return (error(new_tab, i - 1));
		i++;
	}
	new_tab[i - 1] = 0;
	return (new_tab);
}

void	parse_error(t_data *data)
{
	data->exit_status = 1;
	ft_putstr_fd("bash: '", 2);
	ft_putstr_fd(data->input, 2);
	ft_putstr_fd("': parse error\n", 2);
}
