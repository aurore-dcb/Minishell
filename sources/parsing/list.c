/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/23 14:32:25 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
#include "../../libft/libft.h"

void	ft_lstadd_back_cmd_line(cmd_line **lst, cmd_line *new)
{
	cmd_line	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*lst = new;
}

cmd_line	*ft_lstnew_cmd_line(int len)
{
	cmd_line	*elem;

	elem = malloc(sizeof(cmd_line));
	if (!elem)
		return (NULL);
	elem->cmd = malloc(sizeof(char) * len);
	if (!elem->cmd)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

cmd_line	*ft_lstlast_cmd_line(cmd_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	nb_mots_cmd(char *str)
{
	int	mots;
	int	sep;
    char q;

	mots = 0;
	sep = 1;
	while (*str)
	{
        if (*str == 34 || *str == 39)
        {
            q = *str++;
            // *str++;
            while (*str && *str != q)
                str++;
            str++;
        }
        if (*str == '|')
			sep = 1;
		else if (sep == 1)
		{
			mots++;
			sep = 0;
		}
		str++;
	}
	return (mots);
}

int	nb_lettre_cmd(char *s)
{
	int	i;
    char q;

	i = 0;
    while(s[i])
	{
        if (s[i] == 34 || s[i] == 39)
        {
            q = s[i];
            i++;
            while (s[i] && s[i] != q)
                i++;
            if (s[i] == '\0')
                return (i);
            i++;
        }
        if (s[i] == '|')
            return (i);
        i++;
    }	
	return (i);
}

void	split_pipe(char *input, cmd_line **list)
{
	int j;
    char q;
	int n;
	cmd_line *begin;

	if (input == NULL)
		return ;
	begin = *list;
	n = nb_mots_cmd(input);
	while (n)
	{
		if (*input == '|')
			input++;
		ft_lstadd_back_cmd_line(&begin, ft_lstnew_cmd_line(nb_lettre_cmd(input) + 1)); //Nouvel element aloue
		begin = ft_lstlast_cmd_line(begin);
		j = 0;
        while (*input && *input != '|')
        {
            if (*input == 34 || *input == 39)
            {
                q = *input;
				begin->cmd[j++] = *input++; 
                while (*input && *input != q)
					begin->cmd[j++] = *input;
                if (*input == '\0')
                    return ;
				begin->cmd[j++] = *input++;
            }
			begin->cmd[j++] = *input++;
        }
		begin->cmd[j] = '\0';
		n--;
		printf("line = .%s.\n", begin->cmd);
	}
}

// void	fill_cmd_line(char *input, cmd_line **list)
// {
// 	int j;
//     char q;
// 	cmd_line *begin;

// 	if (input == NULL)
// 		return ;
// 	begin = *list;
// 	while (list)
// 	{
// 		if (*input == '|')
// 			input++;
// 		j = 0;
//         while (*input && *input != '|')
//         {
//             if (*input == 34 || *input == 39)
//             {
//                 q = *input;
// 				begin->cmd[j++] = *input; 
//                 input++;
//                 while (*input && *input != q)
// 					begin->cmd[j++] = *input;
//                 if (*input == '\0')
//                     return ;
// 				begin->cmd[j++] = *input;
//                 input++;
//             }
// 			begin->cmd[j++] = *input++;
//         }
// 		begin->cmd[j] = '\0';
// 		begin = begin->next;
// 	}
// }
