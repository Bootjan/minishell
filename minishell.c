/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:35:08 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/18 16:34:47 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC
#include "minishell.h"

int	execute_command(char *command, char ***envp)
{
	int			parse_code;
	static int	last_ret = 0;
	t_tokens	*tokens;

	set_sighandler(sighandler_running);
	parse_code = parse_error(command);
	if (parse_code != 0)
		return (last_ret = 1, print_parse_error(parse_code), 1);
	tokens = find_tokens(command);
	tokens = replace_wildcard_envvar(tokens, last_ret, *envp);
	tokens = remove_quotes_tokens(tokens);
	if (!tokens)
		return (STD_EXIT);
	if (tokens)
		last_ret = executor(tokens, envp);
	free_tokens(&tokens, FREE_2D);
	return (last_ret);
}

int	hide_ctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (-1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		return (-1);
	return (0);
}

int	minishell(char ***envp)
{
	char	*command;
	int		last_ret;

	last_ret = 0;
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
		last_ret = execute_command(command, envp);
		if (command[0] != '\0')
			add_history(command);
		free(command);
	}
	rl_clear_history();
	return (0);
}
