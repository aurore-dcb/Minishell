/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/28 13:40:42 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	parsing(char *input, char **env, cmd_line **list)
{
	t_quotes etat;
    cmd_line *begin;
    token *token;

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
    begin = *list;
    if (!list)
        return (0);
    while (begin)
    {
        token = begin->token;
        while (token)
        {
            if (token->type != LIMITOR)
                token->word = ft_expand(token->word, env);
            token = token->next;
        }
        begin = begin->next;
    }
    // printf("expand : [%s] -> [%s]\n", input, ft_expand(input, env));
    return (1);
}
