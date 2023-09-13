/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/13 13:55:30 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int signalFlag = 0;

// #include <signal.h>
// void handleCtrlC(int signum) {
// 	(void)signum;
// 	signalFlag = 1;
// }

#include "../../headers/minishell.h"

void	display_list(cmd_line *list)
{
	while (list)
	{
		printf("cmd_line = .%s.\n", list->cmd);
		list = list->next;
	}
}

void	display_token(cmd_line *list)
{
	int i;
	token	*token;

	while (list)
	{
		i = 0;
		printf("\ncmd line = [%s]\n", list->cmd);
		token = list->token;
		while (token)
		{
			printf("word : [%s] - type : [%u]\n", token->word, token->type);
			token = token->next;
		}
		while (list->args[i])
		{
			printf("args[%d] = [%s]\n", i, list->args[i]);
			i++;
		}
		list = list->next;
	}
}

void initialize(s_data *data)
{
	data->etat.simple = 0;
	data->etat.doubl = 0;
    data->cmd = NULL;
	data->tab_env = NULL;
}

void free_cmd_in(cmd_line **cmd)
{
	cmd_line *tmp;

	tmp = *cmd;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->in > 2)
				close(tmp->in);
			tmp = tmp->next;
		}
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	s_data		data;

	if (argc != 1)
		return (printf("No argument are needed !\n"), 1);
	data.envp = NULL;
	data.envex = NULL;
	data.exit_status = 0;
	if (!parse_env(env, &data))
		return (0);
	while (1)
	{
		initialize(&data);
		data.input = readline("minishell> ");
		dprintf(1, "input = %s\n", data.input);
		if (data.input)
		{
			if (data.input[0])
			{
				add_history(data.input);
				if (!parsing(&data))
					printf("ERROR -> parsing\n");
				else
					if (ft_pipex(&data) == 1)
						printf("ERROR -> execution\n");
			}
		}
		else
			break;
		free_list(data.cmd);
		if (data.tab_env)
			free_tab(data.tab_env);
	}
	clear_history();
	// rl_clear_history();
	free_all(&data);
}
