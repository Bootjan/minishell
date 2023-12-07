/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 15:35:11 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/04 19:28:26 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	write_here_doc_to_pipe(char **here_doc, int *fd_in)
{
	int	fd[2];

	if (!here_doc || !*here_doc)
		return ;
	if (pipe(fd) == -1)
		perror_exit("Pipe error: ", STD_EXIT);
	if (write(fd[1], *here_doc, ft_strlen(*here_doc)) == -1)
		perror_exit("Write error: ", STD_EXIT);
	free(*here_doc);
	close(fd[1]);
	*fd_in = fd[0];
}

static char	**convert_cmds(t_cmds **cmds)
{
	int		i;
	int		len;
	t_cmds	*current;
	char	**out;

	len = list_len(*cmds);
	out = ft_calloc(len + 1, sizeof(char *));
	if (!out)
		return (free_list(cmds), NULL);
	i = 0;
	current = *cmds;
	while (current)
	{
		out[i++] = current->data;
		current = current->next;
	}
	free_list(cmds);
	return (out);
}

static int	append_cmd( char *command, t_cmds **cmds)
{
	int		end;
	char	*cmd;

	end = 0;
	cmd = compute_without_quotes(command, &end);
	if (!cmd)
		perror_exit("Malloc failed:", STD_EXIT);
	push_back(cmds, cmd);
	return (end);
}

char	**parse_command(char *command, int *fd_in, int *fd_out)
{
	int		i;
	t_cmds	*cmds;
	char	**cmds_char;
	char	*here_doc;

	i = 0;
	cmds = NULL;
	here_doc = NULL;
	while (command[i] && command[i] != '|' && !is_priority(command, i))
	{
		if (command[i] == '<')
			i += set_input(&(command[i + 1]), fd_in, &here_doc);
		else if (command[i] == '>')
			i += set_output(&(command[i + 1]), fd_out);
		else if (command[i] != ' ')
			i += append_cmd(&(command[i]), &cmds);
		else
			i++;
	}
	write_here_doc_to_pipe(&here_doc, fd_in);
	cmds_char = convert_cmds(&cmds);
	if (!cmds_char)
		perror_exit("No commands:", STD_EXIT);
	return (cmds_char);
}
