/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:31:05 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 18:47:21 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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
	while (command[start + i] && !in_array(command[start + i], QUOTES))
	{
		i++;
		(*total_chars)++;
	}
	return (i);
}

static int	compute_total_chars(char *command)
{
	int	i;
	int	total_chars;

	total_chars = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
			i += add_quotes(command, i, &total_chars);
		else
			i += add_text(command, i, &total_chars);
	}
	return (total_chars);
}

char	*compute_without_quotes_export(char *command)
{
	int		total_chars;
	char	*out;

	total_chars = compute_total_chars(command);
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	add_chars(&out, command, total_chars);
	return (out);
}
