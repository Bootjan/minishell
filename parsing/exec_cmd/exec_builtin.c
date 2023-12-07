/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 17:02:44 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/07 14:04:58 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "builtins.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, EXPORT_STR, 7) == 0)
		return (EXPORT_INT);
	if (ft_strncmp(cmd, ECHO_STR, 5) == 0)
		return (ECHO_INT);
	if (ft_strncmp(cmd, ENV_STR, 4) == 0)
		return (ENV_INT);
	if (ft_strncmp(cmd, PWD_STR, 4) == 0)
		return (PWD_INT);
	// if (ft_strncmp(cmd, CD_STR, 3) == 0)
	// 	return (CD_STR);
	if (ft_strncmp(cmd, UNSET_STR, 6) == 0)
		return (UNSET_INT);
	if (ft_strncmp(cmd, EXIT_STR, 5) == 0)
		return (EXIT_INT);
	return (0);
}

int	exec_builtin(char **cmds, char ***envp, int builtin)
{
	int	argc;
	int	return_val;

	argc = 0;
	return_val = 0; // might wanna init with 127
	while (cmds[argc])
		argc++;
	if (builtin == EXPORT_INT)
		return_val = export(argc, cmds, envp);
	else if (builtin == ECHO_INT)
		return_val = echo(argc, cmds, *envp);
	else if (builtin == ENV_INT)
		return_val = env(argc, cmds, *envp);
	else if (builtin == PWD_INT)
		return_val = pwd(argc, cmds, *envp);
	// else if (builtin == CD_INT)
	// 	return_val = cd(argc, cmds, envp);
	else if (builtin == UNSET_INT)
		return_val = unset(argc, cmds, envp);
	else if (builtin == EXIT_INT)
		return_val = exit_b(argc, cmds, envp);
	return (return_val);
}

void	exec_builtin_child(char ***cmds, char ***envp, int builtin)
{
	int	return_val;

	return_val = exec_builtin(*cmds, envp, builtin);
	free_2d_array(cmds, FREE_2D);
	if (return_val)
		_exit(0);
	perror_exit("Builtin error", STD_EXIT);
}

int	do_dup2_parent(int fd_in, int fd_out, int *new_in, int *new_out)
{
	if (fd_in > 2)
	{
		*new_in = dup(STDIN_FILENO);
		if (dup2(fd_in, STDIN_FILENO) == fd_in)
			return (close(*new_in), close(fd_in), 1);
		close(fd_in);
	}
	if (fd_out > 2)
	{
		// if (dup2(STDOUT_FILENO, *old_out) == STDOUT_FILENO)
		// 	if (fd_in > 2)
		// 		return (dup2(*old_in, STDIN_FILENO), close(*old_in), 1);
		*new_out = dup(STDOUT_FILENO);
		if (dup2(fd_out, STDOUT_FILENO) == fd_out)
			return (dup2(*new_in, STDIN_FILENO), \
				close(*new_in), close(fd_out), 1);
	}
	return (0);
}

void	reset_fds(int fd_in, int fd_out, int new_in, int new_out)
{
	if (fd_in > 2)
	{
		dup2(new_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out > 2)
	{
		dup2(new_out, STDOUT_FILENO);
		close(fd_out);
	}
}

int	exec_builtin_parent(char *command, char ***envp, int builtin)
{
	int		fd_in;
	int		fd_out;
	int		new_in;
	int		new_out;
	char	**cmds;
	int		return_val;

	fd_in = -1;
	fd_out = -1;
	cmds = parse_command(command, &fd_in, &fd_out);
	if (do_dup2_parent(fd_in, fd_out, &new_in, &new_out) == 1)
		return (free_2d_array(&cmds, FREE_2D), 1);
	return_val = exec_builtin(cmds, envp, builtin);
	free_2d_array(&cmds, FREE_2D);
	reset_fds(fd_in, fd_out, new_in, new_out);
	return (return_val);
}
