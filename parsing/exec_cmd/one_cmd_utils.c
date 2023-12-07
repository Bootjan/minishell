/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:21:38 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/07 14:41:16 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	skip_over_quote(char *command, int start, int *j)
{
	int		i;
	char	quote;

	i = 1;
	quote = command[start];
	while (command[start + i] && command[start + i] != quote)
		i++;
	(*j) += i - 1;
	return (i + 1);
}

static int	skip_over_text(char *command, int start, int *j)
{
	int	i;

	i = 0;
	while (command[start + i] && !in_array(command[start + i], OPS_TRIM_QUOTES))
		i++;
	(*j) += i;
	return (i);
}

static int	skip_chars(char *command)
{
	int	i;
	int	j;
	int	total_chars;

	i = 0;
	j = 0;
	total_chars = compute_total_chars_cmd(command);
	while (command[i] && j < total_chars)
	{
		if (command[i] == '\"' || command[i] == '\'')
			i += skip_over_quote(command, i, &j);
		else
			i += skip_over_text(command, i, &j);
	}
	return (i);
}

int	skip_redir(char *command, char redir)
{
	if (command[0] == redir)
		return (skip_chars(&(command[1])) + 2);
	return (skip_chars(command)+ 1);
}

char	*compute_first_cmd(char *command)
{
	int		total_chars;
	char	*out;

	total_chars = compute_total_chars_cmd(command);
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	add_chars(&out, command, total_chars);
	return (out);
}
