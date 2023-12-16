/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:59:32 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/16 19:05:55 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*compute_first_cmd(t_tokens *cmd)
{
	t_tokens	*current;

	current = cmd;
	if (!cmd)
		return (NULL);
	while (current)
	{
		if (current->token == CMD)
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

static void	dup_fds(int fd_in, int fd_out)
{
	if (fd_in > 2)
		do_dup2(fd_in, STDIN_FILENO);
	if (fd_out > 2)
		do_dup2(fd_out, STDOUT_FILENO);
}

static void	do_cmd(t_tokens *tokens, char **envp)
{
	int		fd_in;
	int		fd_out;
	char	**cmds;
	char	*path;

	fd_in = -1;
	fd_out = -1;
	cmds = set_in_output(tokens, &fd_in, &fd_out);
	dup_fds(fd_in, fd_out);
	path = compute_path(envp, cmds[0]);
	if (!path)
		print_error_cmd(cmds[0]);
	if (execve(path, cmds, envp) == -1)
		perror_exit("Execve error: ", STD_EXIT);
}

int	execute_one_cmd(t_tokens *cmd, char ***envp)
{
	int		pid;
	int		status;
	int		builtin_int;
	char	*first_cmd;

	status = 0;
	if (!cmd)
		return (0);
	first_cmd = compute_first_cmd(cmd);
	builtin_int = is_builtin(first_cmd);
	if (builtin_int > 0)
		return (execute_builtin_parent(cmd, envp, builtin_int));
	pid = do_fork();
	if (pid == 0)
		do_cmd(cmd, *envp);
	if (pid > 0)
	{
		errno = 0;
		while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
			errno = 0;
	}
	return (check_status(status));
}
