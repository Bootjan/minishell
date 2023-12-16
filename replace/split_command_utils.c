/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_command_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 15:41:28 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/16 15:44:49 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	update_total_words(bool on_word, char c, int *total_words)
{
	if (!on_word && !in_array(c, TRIM_SET))
	{
		(*total_words)++;
		return (true);
	}
	else if (on_word && in_array(c, TRIM_SET))
		return (false);
	return (on_word);
}

int	compute_total_words(char *command)
{
	int		i;
	bool	on_word;
	int		total_words;

	i = 0;
	on_word = false;
	total_words = 0;
	while (command[i])
	{
		on_word = update_total_words(on_word, command[i], &total_words);
		if (is_quote(command[i]) && !is_open_quote(&(command[i])))
			i += skip_quote(&(command[i + 1]), command[i]);
		else
			i++;
	}
	return (total_words);
}

static int	skip_over_word(char *command, int start)
{
	while (command[start] && !in_array(command[start], TRIM_SET))
	{
		if (is_quote(command[start]) && !is_open_quote(&(command[start])))
			start += skip_quote(&(command[start + 1]), command[start]);
		else
			start++;
	}
	return (start);
}

static char	*compute_sub_str(char *command, int *i)
{
	int		end;
	char	*out;

	end = skip_over_word(command, *i);
	out = ft_substr(command, *i, end - *i);
	if (!out)
		return (NULL);
	*i = end;
	return (out);
}

char	**do_split(char *command, char **out)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		while (in_array(command[i], TRIM_SET))
			i++;
		if (!command[i])
			break ;
		out[j] = compute_sub_str(command, &i);
		if (!out[j++])
			return (free_2d_array(&out, FREE_2D), NULL);
	}
	return (out);
}
