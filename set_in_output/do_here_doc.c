/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_here_doc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 11:52:55 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 10:57:08 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_here_doc_to_pipe(char *here_doc, int *fd_in)
{
	int	fd[2];
	int	ret;

	if (!here_doc)
		return ;
	if (pipe(fd) == -1)
	{
		free(here_doc);
		perror_exit("Pipe failed: ", STD_EXIT);
	}
	*fd_in = fd[0];
	ret = write(fd[1], here_doc, ft_strlen(here_doc));
	close(fd[1]);
	free(here_doc);
	if (ret == -1)
		perror_exit("Write failed: ", STD_EXIT);
}

static char	*concat_strs(char *input, char *out)
{
	char	*ret;

	ret = ft_strjoin(input, out);
	free(input);
	free(out);
	if (!ret)
		perror_exit("Malloc error:", STD_EXIT);
	return (ret);
}

static char	*update_input(char *input, char *line)
{
	char	*temp;
	char	*out;

	out = concat_strs(input, line);
	if (!out)
		perror_exit("Concat_strs failed:", STD_EXIT);
	temp = ft_strdup("\n");
	if (!temp)
		perror_exit("ft_strdup failed:", STD_EXIT);
	out = concat_strs(out, temp);
	if (!out)
		perror_exit("Concat_strs failed:", STD_EXIT);
	return (out);
}

static char	*get_input(char *limiter, int lim_len)
{
	char	*input;
	char	*line;

	input = ft_strdup("");
	if (!input)
		perror_exit("Ft_strdup error:", STD_EXIT);
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (free(line), input);
		else
		{
			if (ft_strncmp(line, limiter, lim_len) == 0
				&& line[lim_len] == '\0')
				return (free(line), input);
			input = update_input(input, line);
		}
	}
}

char	*do_here_doc(char *limiter)
{
	int		lim_len;
	char	*here_doc;

	set_sighandler(sighandler_in_heredoc);
	rl_clear_history();
	lim_len = ft_strlen(limiter);
	here_doc = get_input(limiter, lim_len);
	set_sighandler(NULL);
	return (here_doc);
}
