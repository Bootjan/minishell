/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:57:47 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:25:20 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 199309L
# endif

// ### SIGNAL HANDLERS #########################################################
void	sighandler_interactive(int signum);
void	sighandler_running(int signum);
void	sighandler_in_heredoc(int signum);
void	set_sighandler(__sighandler_t sighandler);

#endif