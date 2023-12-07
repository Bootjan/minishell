/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:50:01 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/06 20:10:09 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "parsing.h"
#include "signal_handler.h"

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

static char	*get_input(char *limiter)
{
	char	*input;
	char	*line;
	int		lim_len;

	input = ft_strdup("");
	if (!input)
		perror_exit("Ft_strdup error:", STD_EXIT);
	lim_len = ft_strlen(limiter);
	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_last_signum == SIGINT)
				g_last_signum = 0;
			else
				return (input); // maybe add warning
		}
		else
		{
			if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\0')
				return (free(line), input);
			input = concat_strs(input, line);
			if (!input)
				perror_exit("Concat_strs failed:", STD_EXIT);
		}
	}
}

static int	do_here_doc(char *command, char **here_doc)
{
	int		end;
	char	*limiter;

	set_sighandler(sighandler_heredoc);
	end = 0;
	limiter = NULL;
	limiter = compute_without_quotes(command, &end);
	if (!limiter)
		perror_exit("Malloc failed: ", STD_EXIT);
	*here_doc = get_input(limiter);
	free(limiter);
	return (end + 1);
}

static int	open_file_read(char *command, int *fd_in)
{
	int		end;
	char	*file;

	end = 0;
	file = NULL;
	file = compute_without_quotes(command, &end);
	if (!file)
		perror_exit("Malloc failed: ", STD_EXIT);
	*fd_in = open(file, O_RDONLY);
	free(file);
	if (*fd_in == -1)
		perror_exit("Failed to open file: ", STD_EXIT);
	return (end);
}

int	set_input(char *command, int *fd_in, char **here_doc)
{
	int		i;

	i = 0;
	if (*here_doc)
	{
		free(*here_doc);
		*here_doc = NULL;
	}
	if (*fd_in > 2)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	if (command[0] == '<')
		i = do_here_doc(&(command[1]), here_doc);
	else
		i = open_file_read(&(command[0]), fd_in);
	set_sighandler(sighandler_running);
	return (i + 1);
}
