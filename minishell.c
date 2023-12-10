/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:35:08 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/09 23:52:36 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC
#include <termios.h>
#include <signal.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"
#include "signal_handler.h"
#include "replace.h"



int	execute_command(char *command, char ***envp)
{
	static int	last_ret = 0;
	char		*clean_command;
	char		*tmp;
	char		*replaced_command;

	set_sighandler(sighandler_running);
	tmp = replace_envvar(command, last_ret, *envp);
	replaced_command = replace_wildcard(tmp);
	if (tmp)
		free(tmp);
	if (parse_error(replaced_command))
		return (ft_putendl_fd("Parse error", 2), last_ret = 1, 1);
	clean_command = trim_command(replaced_command);
	free(replaced_command);
	if (clean_command)
		last_ret = do_commands(clean_command, envp);
	if (clean_command)
		free(clean_command);
	return (last_ret);
}

int	hide_ctl()
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (-1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		return (-1);
	return (0);
}

int	minishell(char **old_envp)
{
	char	*command;
	char	**envp;
	int		last_ret;

	last_ret = 0;
	envp = copy_envp(old_envp);
	if (!envp)
		return (1);
	if (hide_ctl() == -1)
		return (1);
	while (true)
	{
		set_sighandler(sighandler_interactive);
		if (last_ret == 0)
			command = readline(PROMPT);
		else
			command = readline(PROMPT_ERR);
		if (command == NULL)
			break ;
		last_ret = execute_command(command, &envp);
		add_history(command);
		free(command);
	}
	clear_history();
	free_2d_array(&envp, FREE_2D);
	return (0);
}
