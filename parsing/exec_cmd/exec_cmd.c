/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/29 15:15:28 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/05 15:18:16 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "replace.h"

int	compute_amount_of_pipes(char *command)
{
	int	i;
	int	total_pipes;

	i = 0;
	total_pipes = 0;
	while (command[i])
		if (command[i++] == '|')
			total_pipes++;
	return (total_pipes);
}

void	update_command(char **command, int pid)
{
	int	pipe_i;

	pipe_i = 0;
	if (pid == 0)
		return ;
	while ((*command)[pipe_i] && (*command)[pipe_i] != '|')
		pipe_i++;
	*command = &((*command)[pipe_i + 1]);
}

int	do_pipe_command(char *command, char **envp, int amount_of_pipes)
{
	int		i;
	int		pid;
	int		status;
	t_pipes	pipes;

	i = 0;
	status = 0;
	ft_bzero(&pipes, sizeof(t_pipes));
	do_first_cmd(&command, envp, &pipes, &pid);
	while (i++ < amount_of_pipes - 1 && pid > 0)
		do_middle_cmd(&command, envp, &pipes, &pid);
	if (pid > 0)
		do_last_cmd(command, envp, pipes, &pid);
	if (pid > 0)
		waitpid(pid, &status, 0);
	wait_for_childs(amount_of_pipes);
	close_pipes(pipes);
	return (check_status(status));
}

int	do_pipes(char *command, int end, char ***envp)
{
	int		amount_of_pipes;
	int		ret;
	char	*sub_command;

	ret = 0;
	sub_command = ft_substr(command, 0, end);
	if (!sub_command)
		return (STD_EXIT);
	amount_of_pipes = compute_amount_of_pipes(sub_command);
	if (amount_of_pipes == 0)
		ret = do_one_cmd(command, envp);
	else
		ret = do_pipe_command(command, *envp, amount_of_pipes);
	return (free(sub_command), ret);
}

int	do_commands(char *command, char ***envp)
{
	int	end;
	int	ret;

	end = 0;
	while (command[end] && !is_priority(command, end))
		end++;
	ret = do_pipes(command, end, envp);
	if (ret == 0 && is_and_prior(command, end))
		ret = do_commands(&(command[end + 2]), envp);
	else if (ret != 0 && is_or_prior(command, end))
		ret = do_commands(&(command[end + 2]), envp);
	return (ret);
}
