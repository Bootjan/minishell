/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:18:10 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/05 13:29:48 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	env(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	while (*envp != NULL)
	{
		if (printf("%s\n", *envp) == -1)
			return (127);
		envp++;
	}
	return (0);
}
