/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 11:55:42 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:49 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_read(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error_open(file_name);
	return (fd);
}

void	set_input(t_tokens *current, int *fd_in, char **here_doc)
{
	if (*here_doc)
	{
		free(*here_doc);
		*here_doc = NULL;
	}
	if (*fd_in > 2)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	if (current->token == HERE_DOC)
		*here_doc = do_here_doc(current->data);
	else if (current->token == REDIR_IN)
		*fd_in = open_file_read(current->data);
}
