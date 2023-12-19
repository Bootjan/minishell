/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 17:45:41 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 13:38:44 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_quotes(char *out, int *j, char *command, int *i)
{
	char	quote;

	quote = command[(*i)++];
	while (command[(*i)] && command[(*i)] != quote)
		out[(*j)++] = command[(*i)++];
	return (out);
}

static char	*add_chars(char *out, char *command, int total_chars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i] && j < total_chars)
	{
		if (is_quote(command[i]) && !is_open_quote(&(command[i])))
			out = add_quotes(out, &j, command, &i);
		else
			out[j++] = command[i++];
	}
	return (out);
}

static int	skip_quotes(char *command, int i, int *total_chars)
{
	char	quote;

	quote = command[i++];
	while (command[i] && command[i] != quote)
	{
		i++;
		(*total_chars)++;
	}
	return (i);
}

static int	compute_total_for_str(char *command)
{
	int	i;
	int	total_chars;

	i = 0;
	total_chars = 0;
	while (command[i])
	{
		if (is_quote(command[i]) && !is_open_quote(&(command[i])))
			i = skip_quotes(command, i, &total_chars);
		else
			total_chars++;
		i++;
	}
	return (total_chars);
}

char	*remove_quotes(char *command)
{
	int		total_chars;
	char	*out;

	if (!command)
		return (ft_strdup(""));
	total_chars = compute_total_for_str(command);
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (free(command), NULL);
	out = add_chars(out, command, total_chars);
	free(command);
	return (out);
}
