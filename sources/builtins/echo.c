/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:46:52 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/07 15:17:09 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	verif_n(char **args)
{
	int	i;
	int	y;
	int	cpt;

	cpt = 1;
	y = 0;
	i = 1;
	while (args[i] && ft_strlen(args[i]) >= 2)
	{
		if (args[i][y] == '-' && args[i][y + 1] == 'n')
		{
			y++;
			while (args[i][y] == 'n')
				y++;
			if (y == (int)ft_strlen(args[i]))
				cpt++;
		}
		else
			return (cpt);
		i++;
		y = 0;
	}
	return (cpt);
}

int	builtin_echo(s_data *data)
{
	int	i;
	int	y;

	y = 0;
	i = verif_n(data->cmd->args);
	if (i > 1)
		y++;
	while (data->cmd->args[i])
	{
		printf("%s", data->cmd->args[i]);
		if (data->cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (y == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
