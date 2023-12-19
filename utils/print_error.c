/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/09 19:51:48 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 16:23:03 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_open(char *file)
{
	ft_putstr_fd("Minishell: \"", STDERR_FILENO);
	if (file)
		ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("\": No such file or directory\n", STDERR_FILENO);
	_exit(STD_EXIT);
}

void	print_error_cmd(char *cmd)
{
	ft_putstr_fd("Minishell: \"", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\": command not found\n", STDERR_FILENO);
	_exit(STD_EXIT);
}

void	print_parse_error(int code)
{
	if (code == UNCL_QUOTES)
		ft_putendl_fd("Parse error\nUnclosed quotes", STDERR_FILENO);
	if (code == UNCL_PAR)
		ft_putendl_fd("Parse error\nUnclosed parenthesis", STDERR_FILENO);
}
