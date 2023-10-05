/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:09:42 by rmeriau           #+#    #+#             */
/*   Updated: 2023/10/05 14:50:50 by aducobu          ###   ########.fr       */
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

extern int	g_exit;

void		signal_cmd(int sig);
void		sig_handler_job(int sig);
void		heredoc_signal(int sig);
void		set_signals(int sig);
void		handle_sigint(int sig);

#endif