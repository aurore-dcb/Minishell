/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:19:02 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/22 15:07:33 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	closed_quotes(char *input, t_quotes *etat)
{
	int	i;

	i = -1;
	// printf("simp = %c\ndoubl = %c\n", 39, 34);
	while (input[++i])
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
	printf("simple = %d\ndouble = %d\n", etat->simple, etat->doubl);
	return (etat->simple == 0 && etat->doubl == 0);
}
