/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:57:47 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/07 11:45:55 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# define _POSIX_C_SOURCE 199309L

# include <signal.h>
# include <stddef.h>
# include <sys/ioctl.h>

extern volatile sig_atomic_t	g_last_signum;
volatile sig_atomic_t			g_last_signum = 0;

void	sighandler_interactive(int signum);
void	sighandler_running(int signum);
void	sighandler_heredoc(int signum);

void	set_sighandler(__sighandler_t sighandler);

#endif