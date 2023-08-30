/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:24:56 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/30 10:40:54 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

int	error_begin_end_cmd(char *input)
{
    int	i;

	i = 0;
    while (input[i] && input[i] == ' ')
        i++;
    if (input[i] && input[i] == '|')
        return (1);
    i = ft_strlen(input) - 1;
    while (i >= 0 && input[i] == ' ')
        i--;
    if (i >= 0 && input[i] == '|')
        return (1);
    return (0);
}

int error_double_pipe(char *input)
{
    int i;
    char q;

    i = 0;
    while (input[i])
    {
        if (input[i] == 34 || input[i] == 39)
        {
            q = input[i];
            i++;
            while (input[i] && input[i] != q)
                i++;
            if (input[i] && input[i] == q)
                i++;
        }
        else if (input[i] == '|')
        {
            if (input[i + 1] && input[i + 1] == '|')
                return (1);
            i++;
        }
        else
            i++;
    }
    return (0);
}

int    error_syntax(cmd_line **list)
{
    cmd_line    *begin;
    token       *token;

    begin = *list;
    while (begin)
    {
        token = begin->token;
        while (token->next)
        {
            if (is_meta(token->next->word[0]) && is_meta(token->word[0]))
                return (1);
            token = token->next;
        }
        begin = begin->next;
    }
    if (token->word[0] == '<' || token->word[0] == '>')
        return (1);
    if (token->word[0] == '|')
        return (1);
    return (0);
}
