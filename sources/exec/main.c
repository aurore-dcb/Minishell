/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 18:20:54 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialize(t_data *data)
{
	data->etat.simple = 0;
	data->etat.doubl = 0;
	data->cmd = NULL;
	data->tab_env = NULL;
}

char	*prompt(void)
{
	char	*input;
	char	*line;

	input = NULL;
	set_signals(1);
	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

void	init_main(t_data *data, char **env)
{
	g_exit = 0;
	data->envp = NULL;
	data->envex = NULL;
	parse_env(env, data);
	handle_shlevel(data);
}

void	main_utils(t_data *data)
{
	if (data->input[0])
	{
		add_history(data->input);
		if (parsing(data))
		{
			ft_pipex(data);
		}
		else
			g_exit = 2;
	}
	free(data->input);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (printf("No argument are needed !\n"), 1);
	init_main(&data, env);
	while (1)
	{
		initialize(&data);
		data.input = prompt();
		if (data.input)
			main_utils(&data);
		else
		{
			if (isatty(0) == 1)
				printf("exit\n");
			return (free_all(&data), g_exit);
		}
		free_list(data.cmd);
		if (data.tab_env)
			free_tab(data.tab_env);
	}
	clear_history();
	free_all(&data);
	return (0);
}
