/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_output_parent.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 15:34:48 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:31 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

static int	open_file_trunc(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	set_output_parent(t_tokens *current, int *fd_out)
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
	if (*fd_out == -1)
		return (1);
	return (0);
}
