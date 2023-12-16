/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:57:09 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:20:50 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_lastsig;

void	sighandler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	g_lastsig = signum;
}

void	sighandler_running(int signum)
{
	if (g_lastsig != signum)
		kill(0, signum);
	g_lastsig = signum;
}

void	sighandler_in_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
		rl_on_new_line();
	}
	else if (signum == SIGQUIT)
	{
	}
	g_lastsig = signum;
}

void	set_sighandler(__sighandler_t sighandler)
{
	struct sigaction	sa;

	if (sighandler == NULL)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
	g_lastsig = 0;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
