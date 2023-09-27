/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/26 17:02:24 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		i;
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

void	initialize(s_data *data)
{
	data->etat.simple = 0;
	data->etat.doubl = 0;
	data->cmd = NULL;
	data->tab_env = NULL;
}

// char    *prompt(void)
// {
//     char    *input;
//     char    *line;

//     set_signals(1);
//     if (isatty(STDIN_FILENO))
//         input = readline("minishell$ ");
//     else
//     {
//         line = get_next_line(STDIN_FILENO);
//         input = ft_strtrim(line, "\n");
//         free(line);
//     }
//     return (input);
// }

int	main(int argc, char **argv, char **env)
{
	s_data	data;

	(void)argv;
	if (argc != 1)
		return (printf("No argument are needed !\n"), 1);
	data.envp = NULL;
	data.envex = NULL;
	data.exit_status = 0;
	parse_env(env, &data);
	handle_shlevel(&data);
	while (1)
	{
		set_signals(1);
		initialize(&data);
		data.input = readline("minishell$ ");
		if (data.input)
		{
			if (data.input[0])
			{
				add_history(data.input);
				if (parsing(&data))
				{
					ft_pipex(&data);
				}
				else
					data.exit_status = 2;
			}
		}
		else
		{
			if (isatty(0) == 1)
				ft_printf("exit\n");
			return (free_all(&data), data.exit_status);
		}
		free_list(data.cmd);
		if (data.tab_env)
			free_tab(data.tab_env);
	}
	clear_history();
	free_all(&data);
}
