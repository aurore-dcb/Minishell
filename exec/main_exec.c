/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:39:53 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/18 10:26:09 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

void main_exec()
{
    char *input;
    
    while((input = readline("minishell> ")) != NULL)
    {
        if (input[0] != '\0')
        {
            add_history(input);
            printf("Vous avez saisi : %s\n", input);
        }
    }
    rl_clear_history();
    free(input);
}


int main(int argc, char **argv, char **env)
{
    (void)argv;
    (void)argc;
    (void)env;
    
    main_exec();   
    return (0);
}