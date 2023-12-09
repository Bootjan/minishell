/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:57:09 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/09 18:47:08 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "minishell.h"

void	sighandler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sighandler_running(int signum)
{
	signal(signum, SIG_IGN);
	kill(0, signum);
}

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		signal(signum, SIG_IGN);
		kill(0, signum);
	}
	else if (signum == SIGQUIT)
	{
		
	}
}

void	set_sighandler(__sighandler_t sighandler)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
