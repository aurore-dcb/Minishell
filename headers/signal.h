/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:09:42 by rmeriau           #+#    #+#             */
/*   Updated: 2023/09/28 10:03:08 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

extern int	g_flag;

void	signal_cmd(int sig);
void	sig_handler_job(int sig);
void	heredoc_signal(int sig);
void	set_signals(int sig);

#endif