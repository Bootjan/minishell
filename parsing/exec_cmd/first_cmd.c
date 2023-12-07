/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:34:25 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/07 01:51:08 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	first_cmd(char *command, char **envp, t_pipes pipes)
{
	int		fd_in;
	int		fd_out;
	char	**cmds;
	char	*path;
	int		builtin_int;

	fd_in = -1;
	fd_out = -1;
	cmds = parse_command(command, &fd_in, &fd_out);
	if (fd_in > 2)
		do_dup2(fd_in, STDIN_FILENO);
	if (fd_out > 2)
		do_dup2(fd_out, STDOUT_FILENO);
	else
		do_dup2(pipes.fd_in_curr, STDOUT_FILENO);
	builtin_int = is_builtin(cmds[0]);
	if (builtin_int > 0)
		exec_builtin_child(&cmds, &envp, builtin_int);
	path = compute_path(envp, cmds[0]);
	if (execve(path, cmds, envp) == -1)
		perror_exit("Execve error: ", STD_EXIT);
}

void	do_first_cmd(char **command, char **envp, t_pipes *pipes, int *pid)
{
	init_pipe(pipes);
	*pid = do_fork();
	if (*pid == 0)
		first_cmd(*command, envp, *pipes);
	update_command(command, *pid);
}
