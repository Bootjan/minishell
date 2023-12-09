/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:57:41 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/09 18:47:15 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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
