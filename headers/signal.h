/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:09:42 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/05 10:37:46 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# ifndef LONG_MAX_EXIT
#  define LONG_MAX_EXIT 9223372036854775807
# endif

# ifndef LONG_MIN_EXIT
#  define LONG_MIN_EXIT -9223372036854775807
# endif

extern int	g_flag;

void		signal_cmd(int sig);
void		sig_handler_job(int sig);
void		heredoc_signal(int sig);
void		set_signals(int sig);
void		handle_sigint(int sig);

#endif