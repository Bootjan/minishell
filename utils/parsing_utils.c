/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 16:31:42 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:17:27 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_status(int status)
{
	if (WIFEXITED(status) == true)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) == true)
		return (WTERMSIG(status));
	return (printf("Child exited abnormally.\n"), 1);
}

int	part_of_subcmd(char c)
{
	return (c && c != ' ' && !in_array(c, OPERATORS));
}

void	perror_exit(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	perror("");
	_exit(exit_code);
}

int	in_array(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}
