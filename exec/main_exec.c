/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/18 14:13:08 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"
#include "../libft/libft.h"

void	main_exec(void)
{
	char	*input;

	input = readline("minishell> ");
	while (input != NULL)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			printf("Vous avez saisi : %s\n", input);
		}
		free(input);
		input = readline("minishell> ");
	}
	free(input);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	(void)env;

	char **cmd;
	cmd = malloc(sizeof(char *) * 5);
	cmd[0] = "echo";
	cmd[1] = "ok";
	cmd[2] = "SUPERR";
	cmd[3] = "1 ";
	cmd[4] = NULL;
	builtin_echo(cmd);
	free(cmd);
	return (0);
}
