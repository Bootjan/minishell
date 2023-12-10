/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:57:36 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/10 00:46:55 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"

int	echo(int argc, char *argv[], char *envp[])
{
	int		i;
	bool	new_line;

	(void) envp;
	i = 1;
	new_line = true;
	if (argc > 1 && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = false;
		i = 2;
	}
	while (i < argc)
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (i++ + 1 < argc)
			write(STDOUT_FILENO, " ", 1);
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
