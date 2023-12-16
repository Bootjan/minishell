/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_token.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 22:46:59 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:13:50 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*compute_command(char *command, int total_chars)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	while (i < total_chars)
	{
		if (is_command(command[j]))
			out[i++] = command[j++];
		else if (command[j] == '\'')
			out = append_squote(out, &i, command, &j);
		else if (command[j] == '\"')
			out = append_dquote(out, &i, command, &j);
		else
			j++;
	}
	return (out);
}

char	*empty_token(char quote)
{
	char		*data;

	data = ft_calloc(3, sizeof(char));
	if (!data)
		return (NULL);
	data[0] = quote;
	data[1] = quote;
	return (data);
}

char	*compute_token(char *command, int *skip)
{
	int		total_chars;
	char	*token;

	if (only_empty_quotes(command))
		return ((*skip) += 2, empty_token(command[0]));
	total_chars = compute_total_chars(command, skip);
	token = compute_command(command, total_chars);
	if (!token)
		return (NULL);
	return (token);
}
