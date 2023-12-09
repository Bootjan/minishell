/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:41:28 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 22:33:47 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

static void	do_cmd(char *command, char ***envp)
{
	int		fd_in;
	int		fd_out;
	char	**cmds;
	char	*path;

	fd_in = -1;
	fd_out = -1;
	cmds = parse_command(command, &fd_in, &fd_out);
	if (fd_in > 2)
		do_dup2(fd_in, STDIN_FILENO);
	if (fd_out > 2)
		do_dup2(fd_out, STDOUT_FILENO);
	path = compute_path(*envp, cmds[0]);
	if (!path)
		print_error_cmd(cmds[0]);
	if (execve(path, cmds, *envp) == -1)
		perror_exit("Execve error: ", STD_EXIT);
}

char	*find_first_cmd(char *command)
{
	int	i;

	i = 0;
	while (command[i] && !is_priority(command, i))
	{
		if (command[i] == '<' || command[i] == '>')
			i += skip_redir(&(command[i + 1]), command[i]);
		else if (command[i] != ' ')
			return (compute_first_cmd(&(command[i])));
		else
			i++;
	}
	return (NULL);
}

int	do_one_cmd(char *command, char ***envp)
{
	int		pid;
	int		status;
	int		builtin_int;
	char	*first_cmd;

	status = 0;
	first_cmd = find_first_cmd(command);
	builtin_int = is_builtin(first_cmd);
	if (first_cmd)
		free(first_cmd);
	if (builtin_int > 0)
		return (exec_builtin_parent(command, envp, builtin_int));
	pid = do_fork();
	if (pid == 0)
		do_cmd(command, envp);
	if (pid > 0)
		waitpid(pid, &status, 0);
	return (check_status(status));
}
