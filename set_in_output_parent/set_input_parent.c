/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_input_parent.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 15:35:19 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:26 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_read(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	set_input_parent(t_tokens *current, int *fd_in, char **here_doc)
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
	if (*fd_in == -1 && !*here_doc)
		return (1);
	return (0);
}
