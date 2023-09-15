/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:09:06 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/15 11:34:02 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	signalFlag = 0;

void	signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		if (signalFlag == 0)
			printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\33[2K\r", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_job(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	heredoc_signal(int sig)
{
	close(0);
	if (sig == SIGINT)
		signalFlag = 1;
	ft_putstr_fd("\n", 2);
}

void	init_signal(void)
{
	signal(SIGINT, sig_handler_job);
	signal(SIGQUIT, sig_handler_job);
}
