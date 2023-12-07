/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_without_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:43:03 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/06 20:14:08 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	add_quotes(char *command, int start, int *total_chars)
{
	int		i;
	char	quote;

	i = 1;
	quote = command[start];
	while (command[start + i] && command[start + i] != quote)
	{
		i++;
		(*total_chars)++;
	}
	return (i + 1);
}

static int	add_text(char *command, int start, int *total_chars)
{
	int	i;

	i = 0;
	while (command[start + i] && !in_array(command[start + i], OPS_TRIM_QUOTES))
	{
		i++;
		(*total_chars)++;
	}
	return (i);
}

int	compute_total_chars_cmd(char *command)
{
	int	i;
	int	total_chars;

	total_chars = 0;
	i = 0;
	while (command[i] && !in_array(command[i], OPS_TRIM))
	{
		if (command[i] == '\"' || command[i] == '\'')
			i += add_quotes(command, i, &total_chars);
		else
			i += add_text(command, i, &total_chars);
	}
	return (total_chars);
}

int	add_chars(char **out, char *command, int total_chars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i] && j < total_chars)
	{
		if (command[i] == '\"')
		{
			i++;
			while (command[i] && command[i] != '\"')
				(*out)[j++] = command[i++];
		}
		else if (command[i] == '\'')
		{
			i++;
			while (command[i] && command[i] != '\'')
				(*out)[j++] = command[i++];
		}
		else
			(*out)[j++] = command[i];
		i++;
	}
	return (i);
}

char	*compute_without_quotes(char *command, int *end)
{
	int		total_chars;
	char	*out;

	total_chars = compute_total_chars_cmd(command);
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	*end = add_chars(&out, command, total_chars);
	return (out);
}
