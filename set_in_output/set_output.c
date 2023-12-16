/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_output.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 11:55:19 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:54 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_error_open(file_name);
	return (fd);
}

static int	open_file_trunc(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error_open(file_name);
	return (fd);
}

void	set_output(t_tokens *current, int *fd_out)
{
	if (*fd_out > 2)
	{
		close(*fd_out);
		*fd_out = -1;
	}
	if (current->token == REDIR_APP)
		*fd_out = open_file_append(current->data);
	else if (current->token == REDIR_TRUNC)
		*fd_out = open_file_trunc(current->data);
}
