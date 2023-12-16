/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_in_output.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 02:08:31 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:46 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**append_cmd_char(char *command, char **cmds_char, int len)
{
	char	**out;

	if (len == 0)
	{
		out = ft_split(command, "");
		if (!out)
			perror_exit("Ft_split failed:", STD_EXIT);
		return (out);
	}
	out = ft_calloc(len + 2, sizeof(char *));
	if (!out)
		perror_exit("Malloc failed:", STD_EXIT);
	out[len] = command;
	while (len-- > 0)
		out[len] = cmds_char[len];
	free(cmds_char);
	return (out);
}

char	**set_in_output(t_tokens *cmd, int *fd_in, int *fd_out)
{
	int			len;
	char		*here_doc;
	char		**cmds_char;
	t_tokens	*current;

	len = 0;
	here_doc = NULL;
	cmds_char = NULL;
	current = cmd;
	while (current && current->token != PIPE)
	{
		if (current->token <= REDIR_IN)
			set_input(current, fd_in, &here_doc);
		else if (current->token <= REDIR_TRUNC)
			set_output(current, fd_out);
		else
			cmds_char = append_cmd_char(current->data, cmds_char, len++);
		current = current->next;
	}
	write_here_doc_to_pipe(here_doc, fd_in);
	return (cmds_char);
}
