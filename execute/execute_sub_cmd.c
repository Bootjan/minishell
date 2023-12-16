/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_sub_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 01:36:58 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:19:27 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*update_command(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	if (!current)
		return (NULL);
	while (current && current->token != PIPE)
		current = current->next;
	if (!current)
		return (NULL);
	return (current->next);
}

int	amount_of_pipes(t_tokens *cmd)
{
	int			pipes;
	t_tokens	*current;

	pipes = 0;
	current = cmd;
	while (current)
	{
		if (current->token == PIPE)
			pipes++;
		current = current->next;
	}
	return (pipes);
}

int	execute_pipes(t_tokens *cmd, char **envp, int amount_of_pipes)
{
	int		pid;
	int		status;
	t_pipes	pipes;

	status = 0;
	ft_bzero(&pipes, sizeof(t_pipes));
	cmd = execute_first_cmd(cmd, envp, &pipes, &pid);
	while (amount_of_pipes-- > 1 && pid > 0)
		cmd = execute_middle_cmd(cmd, envp, &pipes, &pid);
	if (pid > 0)
		pid = execute_last_cmd(cmd, envp, pipes);
	if (pid > 0)
	{
		errno = 0;
		while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
			errno = 0;
	}
	wait_for_childs(amount_of_pipes);
	close_pipes(pipes);
	return (check_status(status));
}

int	execute_sub_cmd(t_tokens *cmd, char ***envp)
{
	int	ret;
	int	pipes;

	ret = 0;
	pipes = amount_of_pipes(cmd);
	if (pipes == 0)
		ret = execute_one_cmd(cmd, envp);
	else
		ret = execute_pipes(cmd, *envp, pipes);
	return (ret);
}
