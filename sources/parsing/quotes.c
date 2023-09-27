/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:19:02 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/26 15:30:59 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	closed_quotes(char *input, t_quotes *etat)
{
	int	i;

	i = -1;
	while (input && i < ft_strlen(input) && input[++i])
	{
		if (input[i] == 39)
		{
			i++;
			etat->simple = 1;
			while (input[i] && input[i] != 39)
				i++;
			if (input[i] && input[i] == 39)
				etat->simple = 0;
		}
		else if (input[i] == 34)
		{
			i++;
			etat->doubl = 1;
			while (input[i] && input[i] != 34)
				i++;
			if (input[i] && input[i] == 34)
				etat->doubl = 0;
		}
	}
	return (etat->simple == 0 && etat->doubl == 0);
}
