/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:57:41 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/06 18:41:17 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	pwd(int argc, char *argv[], char *envp[])
{
	char	*path;

	(void) argc;
	(void) argv;
	(void) envp;
	path = malloc(PATH_MAX);
	if (path == NULL)
		return (1);
	path = getcwd(path, PATH_MAX);
	if (path == NULL)
		return (1); 
	printf("%s\n", path);
	free(path);
	return (0);
}
