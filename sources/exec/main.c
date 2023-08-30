/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/30 14:04:00 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int signalFlag = 0;

// #include <signal.h>
// void handleCtrlC(int signum) {
// 	(void)signum;
// 	signalFlag = 1;
// }

#include "../../headers/exec.h"
#include "../../libft/libft.h"
//#include <signal.h>

void	display_tab(char *input)
{
	int		i;
	char	**tab;

	i = 0;
	tab = split_meta(input, ' ');
	while (tab[i])
	{
		printf(".%s.\n", tab[i]);
		i++;
	}
	free_tab(tab);
}

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
	token	*token;

	while (list)
	{
		printf("\ncmd line = [%s]\n", list->cmd);
		token = list->token;
		while (token)
		{
			printf("word : [%s] - type : [%u]\n", token->word, token->type);
			token = token->next;
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
	data.exit_status = 10;
	data.input = readline("minishell> ");
	data.env = env; // creer une autre variable pour qu'on puisse la modifier lors de l'execution
	// if (signal(SIGINT, handleCtrlC) == SIG_ERR) {
	// perror("Erreur lors de la configuration du gestionnaire de signal");
	// return (1);
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
			else
				display_token(data.cmd);
			// si ctrl-C : sortir de cette boucle
		}
		free_all(&data.cmd, data.input);
		data.input = readline("minishell> ");
	}
	// clear_history();
	rl_clear_history();
	return (0);
}
