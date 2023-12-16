/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:27:28 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/13 16:49:45 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_total_words(const char *str, char *set)
{
	int		i;
	int		on_word;
	int		total_words;
	bool	is_delim;

	i = 0;
	on_word = 0;
	total_words = 0;
	while (str[i])
	{
		is_delim = ft_strchr(set, str[i++]) != NULL;
		if (on_word == 0 && !is_delim)
		{
			total_words++;
			on_word = 1;
		}
		if (is_delim)
			on_word = 0;
		if (!is_delim)
			on_word = 1;
	}
	return (total_words);
}

static int	update_start(const char *str, char *set, int start, int i)
{
	bool	is_delim;

	is_delim = ft_strchr(set, str[i]);
	if (!is_delim && start == -1)
		return (i);
	if (is_delim)
		return (-1);
	return (start);
}

static void	free_array(char **out, int total_words)
{
	int	i;

	i = 0;
	if (!out)
		return ;
	while (i < total_words + 1)
	{
		if (out[i])
			free(out[i]);
		i++;
	}
	if (out)
		free(out);
}

static char	**compute_array(char **out, const char *str, \
char *set, int *error_flag)
{
	int	start;
	int	i;
	int	j;

	start = -1;
	i = 0;
	j = 0;
	while (str[i] && *error_flag == 0)
	{
		if (ft_strchr(set, str[i]) && start >= 0)
		{
			out[j] = ft_substr(str, start, i - start);
			if (!out[j++])
				*error_flag = 1;
		}
		start = update_start(str, set, start, i++);
	}
	if (start >= 0 && *error_flag == 0)
	{
		out[j] = ft_substr(str, start, i - start);
		if (!out[j++])
			*error_flag = 1;
	}
	return (out);
}

char	**ft_split(const char *str, char *set)
{
	char	**out;
	int		total_words;
	int		error_flag;

	if (!set || !str)
		return (NULL);
	total_words = count_total_words(str, set);
	out = (char **)ft_calloc((total_words + 1), sizeof(char *));
	if (!out)
		return (NULL);
	error_flag = 0;
	out = compute_array(out, str, set, &error_flag);
	if (error_flag == 1)
	{
		free_array(out, total_words);
		out = NULL;
	}
	return (out);
}
