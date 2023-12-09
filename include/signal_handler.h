/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:57:47 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/09 18:40:33 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 199309L
#endif

# include <signal.h>
# include <stddef.h>
# include <sys/ioctl.h>

void	sighandler_interactive(int signum);
void	sighandler_running(int signum);
void	sighandler_heredoc(int signum);

typedef void(*__sighandler_t)(int);

void	set_sighandler(__sighandler_t sighandler);

#endif