/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_envvar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 13:08:07 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/07 13:49:57 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "builtins.h"
#include "libft.h"

static int	strlen_to_endofvar(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && !ft_strchr(EXPORT_TRIM, s[len]))
		len++;
	return (len);
}

static char	*strdup_to_endofvar(char *s)
{
	int		size;
	char	*out;

	size = strlen_to_endofvar(s) + 1;
	out = ft_calloc(size, sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s, size - 1);
	return (out);
}

static char *get_envvar(char **envp, char *ptr)
{
	char **current_var;

	current_var = envp;
	while (*current_var != NULL)
	{
		if (ft_strncmp(*current_var, ptr, ft_strlen(ptr)) == 0 && (*current_var)[ft_strlen(ptr)] == '=')
			return (&(*current_var)[ft_strlen(ptr) + 1]);
		current_var++;
	}
	return (NULL);
}

char	*replace_envvar(char *str, int last_ret, char **envp)
{
	char	*replaced_str;
	char	*tmp;
	char	*replacement;
	char	chrstr[2];
	int		i;
	bool	in_quotes;
	bool	in_double_quotes;

	chrstr[1] = '\0';
	in_quotes = false;
	in_double_quotes = false;
	replaced_str = ft_strdup("");
	if (replaced_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !in_quotes)
		{
			i++;
			if (str[i] == '?')
			{
				replacement = ft_itoa(last_ret);
				if (replacement == NULL)
					return (free(replaced_str), NULL);
				tmp = replaced_str;
				replaced_str = ft_strjoin(replaced_str, replacement);
				free(tmp);
				free(replacement);
				i += 1;
			}
			else
			{
				tmp = strdup_to_endofvar(&str[i]);
				if (tmp == NULL)
					return (free(replaced_str), NULL);
				replacement = get_envvar(envp, tmp);
				free(tmp);
				if (replacement != NULL)
				{
					tmp = replaced_str;
					replaced_str = ft_strjoin(replaced_str, replacement);
					free(tmp);
				}
				i += strlen_to_endofvar(&str[i]);
			}
		}
		else
		{
			if (str[i] == '\"' && !in_quotes)
				in_double_quotes = !in_double_quotes;
			if (str[i] == '\'' && !in_double_quotes)
				in_quotes = !in_quotes;
			chrstr[0] = str[i];
			tmp = replaced_str;
			replaced_str = ft_strjoin(replaced_str, chrstr);
			free(tmp);
			i++;
		}
		if (replaced_str == NULL)
			return (NULL);
	}
	return (replaced_str);
}

// #include <stdio.h>



// int main(int argc, char *argv[])
// {
// 	char *replaced_str;
// 	if (argc < 2)
// 		return (1);
	
// 	replaced_str = replace_envvar(argv[1]);
// 	printf("%s -> %s\n", argv[1], replaced_str);
// 	if (replaced_str != NULL)
// 		free(replaced_str);
// 	return (0);
// }