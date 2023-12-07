/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:57:36 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/07 11:41:21 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int	echo(int argc, char *argv[], char *envp[])
{
	bool	new_line;
	int		i;

	(void) envp;
	new_line = true;
	i = 1;
	if (argc > 1 && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = false;
		i = 2;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i++ + 1 < argc)
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}
