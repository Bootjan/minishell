/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:38:45 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 22:31:12 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	last_cmd(char *command, char **envp, t_pipes pipes)
{
	int		fd_in;
	int		fd_out;
	int		builtin_int;
	char	**cmds;
	char	*path;

	fd_in = -1;
	fd_out = -1;
	cmds = parse_command(command, &fd_in, &fd_out);
	if (fd_in > 2)
		do_dup2(fd_in, STDIN_FILENO);
	else
		do_dup2(pipes.fd_out_curr, STDIN_FILENO);
	if (fd_out > 2)
		do_dup2(fd_out, STDOUT_FILENO);
	builtin_int = is_builtin(cmds[0]);
	if (builtin_int > 0)
		exec_builtin_child(&cmds, &envp, builtin_int);
	path = compute_path(envp, cmds[0]);
	if (!path)
		print_error_cmd(cmds[0]);
	if (execve(path, cmds, envp) == -1)
		perror_exit("Execve error: ", STD_EXIT);
}

void	do_last_cmd(char *command, char **envp, t_pipes pipes, int *pid)
{
	close(pipes.fd_in_curr);
	if (pipes.fd_out_prev > 2)
		close(pipes.fd_out_prev);
	*pid = fork();
	if (*pid == 0)
		last_cmd(command, envp, pipes);
}
