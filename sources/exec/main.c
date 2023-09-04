/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/04 13:41:41 by aducobu          ###   ########.fr       */
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
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	s_data		data;
	if (argc != 1)
		return (printf("No argument are needed !\n"), 1);
	data.envp = NULL;
	data.exit_status = 0;
	data.input = readline("minishell> ");
	// data.env = env; // creer une autre variable pour qu'on puisse la modifier lors de l'execution
	// if (signal(SIGINT, handleCtrlC) == SIG_ERR) {
	// perror("Erreur lors de la configuration du gestionnaire de signal");
	// return (1);
	// }
	if (!parse_env(env, &data))
		return (0);
	// while (data.envp)
	// {
	// 	printf("%s\n", data.envp->data);
	// 	data.envp = data.envp->next;
	// }
	while (/*signalFlag == 0 &&*/ data.input != NULL)
	{
		initialize(&data);
		if (/*signalFlag == 0 && */ data.input[0] != '\0')
		{
			add_history(data.input);
			// -> traiter input : parsing puis execution
			if (!parsing(&data))
				printf("ERROR -> parsing\n");
			else //exec
			{
				// display_token(data.cmd);
				if (ft_pipex(&data))
					printf("ERROR -> execution\n");
			}
			// printf("%d\n", ft_strcmp(data.cmd->args[0], "cd"));
			// else if (ft_strcmp(data.cmd->args[0], "cd") == 0)
            // {
            //     build_cd(&data);
            // }
            // else if (ft_strcmp(data.cmd->args[0], "pwd") == 0)
            // {
            //     builtin_pwd(&data);
            // }
            // else if (ft_strcmp(data.cmd->args[0], "env") == 0)
            // {
            //     // printf("select env\n");
            //     builtin_env(&data);
			//si ctrl-C : sortir de cette boucle
		}
		free_all(&data.cmd, data.input);
		data.input = readline("minishell> ");
	}
	// clear_history();
	rl_clear_history();
	return (0);
}
