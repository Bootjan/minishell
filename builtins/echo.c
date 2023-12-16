/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:57:36 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:05 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(int argc, char **argv, int i)
{
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if (i++ + 1 < argc)
			ft_putstr(" ");
	}
}

static bool	check_nl_flag(int argc, char **argv, int *i)
{
	if (argc > 1 && ft_strncmp(argv[1], "-n", 3) == 0)
		return (*i = 2, false);
	return (true);
}

int	echo(int argc, char *argv[], char *envp[])
{
	int		i;
	bool	new_line;

	(void)envp;
	i = 1;
	new_line = check_nl_flag(argc, argv, &i);
	print_args(argc, argv, i);
	if (new_line)
		ft_putstr("\n");
	return (0);
}
