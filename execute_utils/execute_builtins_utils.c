/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtins_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 01:40:51 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:16:52 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, EXPORT_STR, 7) == 0)
		return (EXPORT_INT);
	if (ft_strncmp(cmd, ECHO_STR, 5) == 0)
		return (ECHO_INT);
	if (ft_strncmp(cmd, ENV_STR, 4) == 0)
		return (ENV_INT);
	if (ft_strncmp(cmd, PWD_STR, 4) == 0)
		return (PWD_INT);
	if (ft_strncmp(cmd, CD_STR, 3) == 0)
		return (CD_INT);
	if (ft_strncmp(cmd, UNSET_STR, 6) == 0)
		return (UNSET_INT);
	if (ft_strncmp(cmd, EXIT_STR, 5) == 0)
		return (EXIT_INT);
	return (0);
}

int	execute_builtin(char **cmds, char ***envp, int builtin)
{
	int	argc;
	int	return_val;

	argc = 0;
	return_val = STD_EXIT;
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
	else if (builtin == CD_INT)
		return_val = cd(argc, cmds, envp);
	else if (builtin == UNSET_INT)
		return_val = unset(argc, cmds, envp);
	else if (builtin == EXIT_INT)
		return_val = exit_b(argc, cmds, envp);
	return (return_val);
}
