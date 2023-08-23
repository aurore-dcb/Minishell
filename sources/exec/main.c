/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/23 13:57:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	cmd_line	*list;
	
	(void)env;
	(void)argv;
	if (argc != 1)
		return (printf("No argument are needed !\n"), 1);
	input = readline("minishell> ");
	while (input != NULL)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			// -> traiter input : parsing puis execution
			if (!parsing(input, env))
				return (1);
			split_pipe(input, &list);
			// printf("etat quotes = %d\n", closed_quotes(input, &etat));
			// display_tab(input);
		}
		free(input);
		input = readline("minishell> ");
	}
	free(input);
	rl_clear_history();
	return (0);
}
