/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:40:16 by rmeriau           #+#    #+#             */
/*   Updated: 2023/08/25 10:58:36 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

void ft_strcpy_pos(char *dst, char *src, int start, int end)
{
	int i;
	
	i = 0;
	while (src[start] && start < end)
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
}

t_type   get_type_meta(char *word)
{
    int len;

    len = ft_strlen(word);
    if (len == 1)
    {
        if (word[0] == '>')
            return (FILE_OUT);
        else if (word[0] == '<')
            return (FILE_IN);
    }
    else if (len == 2)
    { 
        if (word[0] == '>' && word[1] == '>')
            return (FILE_OUT_SUR);
        else if (word[0] == '<' && word[1] == '<')
            return (HERE_DOC);
    }
    if (len > 0)
        return (ARG);
    return (NONE);
} 

void   get_type(token *lst)
{
    lst = lst->next;
    while (lst)
    {
        if (lst->previous->type == FILE_IN && lst->type == ARG)
            lst->type = OPEN_FILE;
        else if (lst->previous->type == HERE_DOC && lst->type == ARG)
            lst->type = LIMITOR;
        else if (lst->previous->type == FILE_OUT && lst->type == ARG)
            lst->type = EXIT_FILE;
        else if (lst->previous->type == FILE_OUT_SUR && lst->type == ARG)
            lst->type = EXIT_FILE_RET;
        lst = lst->next;
    }
}

token	*ft_lstnew_token(cmd_line *list, int start, int end)
{
	token	*elem;

	elem = malloc(sizeof(token));
	if (!elem)
		return (NULL);
	elem->word = (char *)malloc(sizeof(char) * (end - start + 1));;
	if (!elem->word)
		return (NULL);
	ft_strcpy_pos(elem->word, list->cmd, start, end);
    elem->type = get_type_meta(elem->word);
	elem->next = NULL;
    elem->previous = NULL;
	return (elem);
}

int	ft_lstadd_back_token(token **lst, token *new)
{
	token	*list;

    if (!new)
    {
        return (1);
    }
    list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
        list->next->previous = list; 
	}
	else
		*lst = new;
    return (0);
}

void	add_word(cmd_line *list)
{
	int		i;
	int 	start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	list->token = NULL;
	while (list->cmd[i])
	{
		while (list->cmd[i] == ' ' && list->cmd[i])
			i++;
		start = i;
		while (list->cmd[i] != ' ' && list->cmd[i])
			i++;
		end = i;
		printf("word size == %d\n", end - start);
		if (ft_lstadd_back_token(&list->token, ft_lstnew_token(list, start, end)))
        {
            // free
            return ;
        }
	}
    get_type(list->token);
    //Affichage de la liste (a retirer)
	while (list->token->next)
	{
        list->token = list->token->next;
		printf("word = .%s.   previous = .%s.   type = %d\n", list->token->word, list->token->previous->word, list->token->type);
	}
}

void	split_word(cmd_line *list)
{
	while (list)
	{
		list->cmd = ft_strtrim(list->cmd, " ");
		add_word(list);
		list = list->next;
	}
}
