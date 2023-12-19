/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_last_cmd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 02:05:17 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 11:26:26 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_fds(int fd_in, int fd_out, t_pipes pipes)
{
	if (fd_in > 2)
		do_dup2(fd_in, STDIN_FILENO);
	else
		do_dup2(pipes.fd_out_curr, STDIN_FILENO);
	if (fd_out > 2)
		do_dup2(fd_out, STDOUT_FILENO);
}

static void	last_cmd(t_tokens *cmd, char **envp, t_pipes pipes)
{
	int		fd_in;
	int		fd_out;
	int		builtin_int;
	char	*path;
	char	**cmds;

	fd_in = -1;
	fd_out = -1;
	cmds = set_in_output(cmd, &fd_in, &fd_out);
	if (!cmds)
		print_error_cmd("");
	dup_fds(fd_in, fd_out, pipes);
	builtin_int = is_builtin(cmds[0]);
	if (builtin_int > 0)
		execute_builtin_child(cmds, envp, builtin_int);
	path = compute_path(envp, cmds[0]);
	if (!path)
		print_error_cmd(cmds[0]);
	if (execve(path, cmds, envp) == -1)
		perror_exit("Execve error: ", STD_EXIT);
}

int	execute_last_cmd(t_tokens *cmd, char **envp, t_pipes pipes)
{
	int	pid;

	close(pipes.fd_in_curr);
	if (pipes.fd_out_prev > 2)
		close(pipes.fd_out_prev);
	pid = fork();
	if (pid == 0)
		last_cmd(cmd, envp, pipes);
	return (pid);
}
