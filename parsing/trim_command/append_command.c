/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:15:02 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/06 20:15:04 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*append_squote(char *out, int *i, char *command, int *start)
{
	if (command[*start] == '\'' && command[*start + 1] == '\'')
	{
		(*start) += 2;
		return (out);
	}
	out[(*i)++] = command[(*start)++];
	while (command[*start] != '\'')
		out[(*i)++] = command[(*start)++];
	out[(*i)++] = command[(*start)++];
	return (out);
}

static char	*append_dquote(char *out, int *i, char *command, int *start)
{
	if (command[*start] == '\"' && command[*start + 1] == '\"')
	{
		(*start) += 2;
		return (out);
	}
	out[(*i)++] = command[(*start)++];
	while (command[*start] != '\"')
		out[(*i)++] = command[(*start)++];
	out[(*i)++] = command[(*start)++];
	return (out);
}

static int	compute_total_chars(char *command, int *i)
{
	int	state;
	int	total_chars;

	state = 0;
	total_chars = 0;
	while (command[*i])
	{
		if (update_total_squote(command, i, &total_chars, &state) == -1)
			return (total_chars);
		if (update_total_dquote(command, i, &total_chars, &state) == -1)
			return (total_chars);
		if (update_total_ops(command, i, &total_chars, &state) == -1)
			return (total_chars);
		if (update_total_cmd(command, i, &total_chars, &state) == -1)
			return (total_chars);
		while (in_array(command[*i], TRIM_SET))
		{
			(*i)++;
			if (state == 1)
				state = 3;
		}
	}
	return (total_chars);
}

static char	*compute_command(char *command, int start, int total_chars)
{
	int		i;
	char	*out;

	i = 0;
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	while (i < total_chars)
	{
		if (is_command(command[start]) || in_array(command[start], OPERATORS))
			out[i++] = command[start++];
		else if (command[start] == '\'')
			out = append_squote(out, &i, command, &start);
		else if (command[start] == '\"')
			out = append_dquote(out, &i, command, &start);
		else
			start++;
	}
	return (out);
}

int	append_command(char *command, int start, t_tokens **tokens, int *error_flag)
{
	int		i;
	int		total_chars;
	char	*str;

	i = start;
	total_chars = compute_total_chars(command, &i);
	str = compute_command(command, start, total_chars);
	if (!str)
		return (*error_flag = 1, 0);
	append_back(str, tokens, error_flag);
	if (*error_flag != 0)
		return (free(str), 0);
	return (i - start);
}
