/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:06:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/19 16:18:50 by rmeriau          ###   ########.fr       */
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

	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			q = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != q)
				i++;
			if (cmd[i] == '\0' || cmd[i] == q)
			{
				i++;
				return (i);
			}
			i++;
		}
		if (cmd[i] == ' ' || cmd[i] == '<' || cmd[i] == '>')
			return (i);
		i++;
	}
	return (i);
}
