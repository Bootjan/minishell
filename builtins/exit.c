/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:52:12 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/07 14:04:09 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	exit_b(int argc, char *argv[], char ***envp)
{
	(void) argc;
	(void) argv;
	free_2d_array(envp, FREE_2D);
	printf("exit\n");
	exit(0);
	return (0);
}
