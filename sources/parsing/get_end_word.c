/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:06:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/21 12:12:35 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	end_except(char *cmd, int i)
{
	if (cmd[i] == '<')
	{
		i++;
		if (cmd[i] == '<')
			i++;
		return (i);
	}
	if (cmd[i] == '>')
	{
		i++;
		if (cmd[i] == '>')
			i++;
		return (i);
	}
	return (i);
}

int	get_end_word(char *cmd, int i)
{
	char	q;
	int		tmp;

	tmp = end_except(cmd, i);
	if (tmp != i)
		return (tmp);
	while (cmd[tmp])
	{
		if (cmd[tmp] == 34 || cmd[tmp] == 39)
		{
			q = cmd[tmp];
			tmp++;
			while (cmd[tmp] && cmd[tmp] != q)
				tmp++;
			if (cmd[tmp] == '\0' || cmd[tmp] == q)
				return (++tmp);
			tmp++;
		}
		if (cmd[tmp] == ' ' || cmd[tmp] == '<' || cmd[tmp] == '>')
			return (tmp);
		tmp++;
	}
	return (tmp);
}
