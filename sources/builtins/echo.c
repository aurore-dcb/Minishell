/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:46:52 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 17:47:12 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	test_arg(char **args, int i)
{
	int	y;

	y = 0;
	if (args[i][0] == '-' && args[i][1] == 'n')
	{
		y++;
		while (args[i][y] == 'n')
			y++;
		if (y == (int)ft_strlen(args[i]))
			return (1);
		else if (args[i][y] != 'n')
			return (0);
	}
	return (0);
}

int	nb_option(char **args)
{
	int	i;
	int	cpt;

	i = 1;
	cpt = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
			cpt++;
		i++;
	}
	return (cpt);
}

int	verif_n(char **args)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 1;
	while (args[i])
	{
		if (test_arg(args, i))
			cpt += 1;
		else
			return (cpt);
		i++;
	}
	return (cpt);
}

void	print_echo(t_cmd_line *cmd, int i, int y)
{
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (y == 0)
		printf("\n");
}

int	builtin_echo(t_cmd_line *cmd)
{
	int	i;
	int	y;
	int	nb_op;
	int	verif;

	i = 1;
	y = 0;
	verif = verif_n(cmd->args);
	nb_op = nb_option(cmd->args);
	if ((nb_op == verif) && (nb_op != 0))
	{
		i = verif + 1;
		y = 1;
	}
	else if (cmd->args[1] && test_arg(cmd->args, 1))
	{
		i = verif + 1;
		y = 1;
	}
	print_echo(cmd, i, y);
	g_exit = 0;
	return (EXIT_SUCCESS);
}
