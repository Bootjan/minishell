/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_in_output_parent.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 15:35:37 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/18 10:46:08 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_1d_2d(char *command)
{
	char	**out;

	out = ft_calloc(2, sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = command;
	return (out);
}

static char	**append_cmd_char_parent(char *command, \
char **cmds_char, int len, int *error_flag)
{
	char	**out;

	if (len == 0)
	{
		out = convert_1d_2d(command);
		if (!out)
			return (*error_flag = 1, NULL);
		return (out);
	}
	out = ft_calloc(len + 2, sizeof(char *));
	if (!out)
		return (free_2d_array(&cmds_char, FREE_1D), *error_flag = 1, NULL);
	out[len] = command;
	while (len-- > 0)
		out[len] = cmds_char[len];
	free(cmds_char);
	return (out);
}

static void	close_free_all(t_builtin_fds fds, char **here_doc, char **cmds_char)
{
	if (fds.fd_in > 2)
		close(fds.fd_in);
	if (fds.fd_out > 2)
		close(fds.fd_out);
	if (*here_doc)
		free(*here_doc);
	*here_doc = NULL;
	free_2d_array(&cmds_char, FREE_2D);
}

char	**set_in_output_parent(t_tokens *cmd, \
t_builtin_fds *fds, char **here_doc)
{
	int			len;
	int			error_flag;
	char		**cmds_char;
	t_tokens	*current;

	len = 0;
	error_flag = 0;
	cmds_char = NULL;
	current = cmd;
	while (current && current->token != PIPE && error_flag == 0)
	{
		if (current->token <= REDIR_IN)
			error_flag = set_input_parent(current, &(fds->fd_in), here_doc);
		else if (current->token <= REDIR_TRUNC)
			error_flag = set_output_parent(current, &(fds->fd_out));
		else
			cmds_char = append_cmd_char_parent(current->data, \
			cmds_char, len++, &error_flag);
		current = current->next;
	}
	if (error_flag != 0 || !cmds_char)
		return (close_free_all(*fds, here_doc, cmds_char), NULL);
	return (ft_free_str(here_doc), cmds_char);
}
