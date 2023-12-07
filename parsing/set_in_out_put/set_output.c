/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_output.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 14:47:08 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/04 19:28:21 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	open_file_write(char *command, int *fd_out)
{
	char	*file;
	int		end;

	end = 0;
	file = compute_without_quotes(command, &end);
	if (!file)
		perror_exit("Malloc failed:", STD_EXIT);
	*fd_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(file);
	if (*fd_out == -1)
		perror_exit("Failed to open file:", STD_EXIT);
	return (end);
}

static int	open_file_append(char *command, int *fd_out)
{
	char	*file;
	int		end;

	end = 0;
	file = compute_without_quotes(command, &end);
	if (!file)
		perror_exit("Malloc failed:", STD_EXIT);
	*fd_out = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(file);
	if (*fd_out == -1)
		perror_exit("Failed to open file:", STD_EXIT);
	return (end + 1);
}

int	set_output(char *command, int *fd_out)
{
	int	i;

	i = 0;
	if (*fd_out > 2)
		close(*fd_out);
	if (command[0] == '>')
		i = open_file_append(&(command[1]), fd_out);
	else
		i = open_file_write(command, fd_out);
	return (i + 1);
}
