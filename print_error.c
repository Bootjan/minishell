/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:51:48 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/09 22:37:23 by bootjan          ###   ########.fr       */
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
