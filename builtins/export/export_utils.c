/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 14:31:05 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/07 11:22:18 by tsteur        ########   odam.nl         */
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

// static int	add_chars(char **out, char *command, int total_chars)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (command[i] && j < total_chars)
// 	{
// 		if (command[i] == '\"')
// 		{
// 			i++;
// 			while (command[i] && command[i] != '\"')
// 				(*out)[j++] = command[i++];
// 		}
// 		else if (command[i] == '\'')
// 		{
// 			i++;
// 			while (command[i] && command[i] != '\'')
// 				(*out)[j++] = command[i++];
// 		}
// 		else
// 			(*out)[j++] = command[i];
// 		i++;
// 	}
// 	return (i);
// }

char	*compute_without_quotes_export(char *command)
{
	int		total_chars;
	char	*out;
	int		i;

	total_chars = compute_total_chars(command);
	i = 0;
	out = ft_calloc(total_chars + 1, sizeof(char));
	if (!out)
		return (NULL);
	add_chars(&out, command, total_chars);
	return (out);
}
