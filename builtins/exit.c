/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:52:12 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:16 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_b(int argc, char *argv[], char ***envp)
{
	(void)argc;
	(void)argv;
	free_2d_array(envp, FREE_2D);
	write(STDOUT_FILENO, "exit\n", 5);
	_exit(0);
}
