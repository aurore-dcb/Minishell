/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/23 14:08:20 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	parsing(char *input, char **env)
{
	t_quotes etat;
    // cmd_line *cmd_line;

    etat.simple = 0;
    etat.doubl = 0;
	if (!env)
		return (0);
    if (closed_quotes(input, &etat) == 0)
        return (0);
    // cmd_line->cmd = NULL;
    
    return (1);
}
