/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:57:41 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:30 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc, char *argv[], char *envp[])
{
	char	*path;

	(void)argc;
	(void)argv;
	(void)envp;
	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (path == NULL)
		return (1);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
