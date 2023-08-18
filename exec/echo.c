/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:46:52 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/18 14:24:10 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"
#include "../libft/libft.h"

int	len_tab(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd[0])
		return (0);
	while (cmd[i])
		i++;
	return (i);
}

// -n ne met pas de \n et forcement en 2e position
void	builtin_echo(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd[1] && ft_strnstr(cmd[1], "-n", 2))
	{
		i = 2;
		while (i < len_tab(cmd) - 1)
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("%s", cmd[i]);
	}
	else
	{
		i = 1;
		while (i < len_tab(cmd) - 1)
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("%s\n", cmd[i]);
	}
}
