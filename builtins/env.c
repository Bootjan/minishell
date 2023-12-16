/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:18:10 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:14 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(int argc, char *argv[], char *envp[])
{
	int	i;

	i = 0;
	(void)argc;
	(void)argv;
	while (envp[i])
		if (printf("%s\n", envp[i++]) == -1)
			return (STD_EXIT);
	return (0);
}
