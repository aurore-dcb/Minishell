/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/30 10:35:40 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"



int expansion(cmd_line **cmd, char **env, int exit_status)
{
    token *token;
    cmd_line *begin;
    
    begin = *cmd;
    if (!cmd)
        return (0);
    while (begin)
    {
        token = begin->token;
        while (token)
        {
            if (token->type != LIMITOR)
            {
                token->word = ft_expand(token->word, env, exit_status);
                if (!token->word)
                    return (0);
            }    
            token = token->next;
        }
        begin = begin->next;
    }
    return (1);
}

int	parsing(char *input, char **env, t_quotes *etat, cmd_line **list, int exit_status)
{
	if (!env)
		return (0);
    if (closed_quotes(input, etat) == 0)
        return (0);
    if (error_begin_end_cmd(input) == 1)
        return (0);
    if (error_double_pipe(input) == 1)
        return (0);
    if (!split_pipe(input, list))
        return (0);
    if (error_syntax(list))
        return (0);
    if (!expansion(list, env, exit_status))
        return (0);
    return (1);
}
