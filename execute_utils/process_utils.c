/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 01:58:11 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 11:13:52 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_pipes *pipes)
{
	int	fd[2];

	if (pipes->fd_in_curr)
	{
		pipes->fd_in_prev = pipes->fd_in_curr;
		pipes->fd_out_prev = pipes->fd_out_curr;
	}
	if (pipe(fd) == -1)
		perror_exit("Init pipe:", STD_EXIT);
	pipes->fd_in_curr = fd[1];
	pipes->fd_out_curr = fd[0];
}

void	close_pipes(t_pipes pipes)
{
	if (pipes.fd_in_curr)
	{
		close(pipes.fd_in_curr);
		close(pipes.fd_out_curr);
	}
	if (pipes.fd_in_prev)
	{
		close(pipes.fd_in_prev);
		close(pipes.fd_out_prev);
	}
}

int	do_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("Fork error:", STD_EXIT);
	return (pid);
}

void	do_dup2(int fd, int new_fd)
{
	int	dup_check;

	dup_check = dup2(fd, new_fd);
	if (dup_check != new_fd)
		perror_exit("Dup2 error:", STD_EXIT);
}

void	wait_for_childs(int num)
{
	int	i;

	i = 0;
	errno = 0;
	while (i < num)
	{
		if (wait(NULL) == -1 && errno == EINTR)
			errno = 0;
		else
			i++;
	}
}
