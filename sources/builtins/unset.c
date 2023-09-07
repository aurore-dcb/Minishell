/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:34:05 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/06 17:26:46 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	del_var(t_env **head, char *arg)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current && ft_strcmp(current->key, arg) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (prev == NULL)
		*head = current->next;
	else
		prev->next = current->next;
	free(current->key);
	free(current->data);
	free(current);
}

void	builtin_unset(s_data *data)
{
	int		i;
	char	**args;

	i = 1;
	args = data->cmd->args;
	while (args[i])
	{
		if (args[i][0] && args[i][0] == '-')
		{
			printf("bash: unset: %s: invalid option\n", args[i]);
			i++;
			continue ;
		}		
		if (in_env(data->envex, args[i]))
			del_var(&data->envex, args[i]);
		if (in_env(data->envp, args[i]))
			del_var(&data->envp, args[i]);
		i++;
	}
}
