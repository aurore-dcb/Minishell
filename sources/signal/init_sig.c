/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:09:06 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/05 17:16:22 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		g_exit = 0;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_job(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	heredoc_signal(int sig)
{
	close(0);
	if (sig == SIGINT)
		g_exit = 130;
	ft_putstr_fd("\n", 2);
}

void	set_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 2)
	{
		signal(SIGINT, sig_handler_job);
		signal(SIGQUIT, sig_handler_job);
	}
	if (sig == 4)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
