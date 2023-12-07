/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 16:31:42 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/05 12:41:20 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <string.h>

#include "parsing.h"

int	check_status(int status)
{
	if (WIFEXITED(status) == true)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) == true)
	{
		//printf("%s\n", sys_siglist[WIFSIGNALED(status)]);
		return (WTERMSIG(status));
	}
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
