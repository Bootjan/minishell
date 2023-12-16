/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 12:06:21 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:18:30 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_child(char	**cmds, char **envp, int builtin_int)
{
	int	return_val;

	return_val = execute_builtin(cmds, &envp, builtin_int);
	free_2d_array(&cmds, FREE_2D);
	if (return_val)
		perror_exit("Builtin error", STD_EXIT);
	_exit(0);
}

int	do_dup2_parent(t_builtin_fds *fds)
{
	if (fds->fd_in > 2)
	{
		fds->new_in = dup(STDIN_FILENO);
		if (dup2(fds->fd_in, STDIN_FILENO) == fds->fd_in)
			return (close(fds->new_in), close(fds->fd_in), 1);
		close(fds->fd_in);
	}
	if (fds->fd_out > 2)
	{
		fds->new_out = dup(STDOUT_FILENO);
		if (dup2(fds->fd_out, STDOUT_FILENO) == fds->fd_out)
			return (dup2(fds->new_in, STDIN_FILENO), close(fds->new_in),
				close(fds->fd_out), 1);
		close(fds->fd_out);
	}
	return (0);
}

void	reset_fds(t_builtin_fds fds)
{
	if (fds.fd_in > 2)
	{
		dup2(fds.new_in, STDIN_FILENO);
		close(fds.new_in);
	}
	if (fds.fd_out > 2)
	{
		dup2(fds.new_out, STDOUT_FILENO);
		close(fds.new_out);
	}
}

int	execute_builtin_parent(t_tokens *tokens, char ***envp, int builtin)
{
	t_builtin_fds	fds;
	char			*here_doc;
	char			**cmds;
	int				return_val;

	here_doc = NULL;
	ft_memset(&fds, -1, sizeof(t_builtin_fds));
	cmds = set_in_output_parent(tokens, &fds, &here_doc);
	if (!cmds)
		return (STD_EXIT);
	if (do_dup2_parent(&fds) == 1)
		return (free_2d_array(&cmds, FREE_1D), STD_EXIT);
	return_val = execute_builtin(cmds, envp, builtin);
	free(cmds);
	reset_fds(fds);
	return (return_val);
}
