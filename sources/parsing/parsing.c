/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/25 14:00:46 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	parsing(char *input, char **env, cmd_line **list)
{
	t_quotes etat;

    etat.simple = 0;
    etat.doubl = 0;
	if (!env)
		return (0);
    if (closed_quotes(input, &etat) == 0)
        return (0);
    if (error_begin_end_cmd(input) == 1)
        return (0);
    if (error_double_pipe(input) == 1)
        return (0);
    if (!split_pipe(input, list))
        return (0);
    printf("expand : [%s] -> [%s]\n", input, ft_expand(input));
    return (1);
}