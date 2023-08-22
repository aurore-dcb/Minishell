/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/22 13:52:37 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_quotes
{
	int	simple;
	int	doubl;
}		t_quotes;

// pwd.c
void	builtin_pwd(char **env);
// env.c
void	builtin_env(char **env);
// cd.c
void	builtin_cd(char *chemin);
// echo.c
void	builtin_echo(char **cmd);

// quotes.c
int		closed_quotes(char *input, t_quotes *etat);

#endif