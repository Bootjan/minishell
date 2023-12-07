/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_wildcard.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 11:24:57 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/04 09:50:14 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stddef.h>
#include <stdbool.h>

#include "libft.h"

#define WORKING_DIR "."

char *list_working_dir(void)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*list;
	char			*tmp;
	
	dir = opendir(WORKING_DIR);
	if (dir == NULL)
		return (NULL);
	list = ft_strdup("");
	ent = readdir(dir);
	while (ent != NULL && list != NULL)
	{
		if (ent->d_name[0] != '.')
		{
			tmp = list;
			list = ft_strjoin(list, ent->d_name);
			free(tmp);
		}
		ent = readdir(dir);
		if (ent != NULL && ent->d_name[0] != '.' && list != NULL && list[0] != '\0')
		{
			tmp = list;
			list = ft_strjoin(list, " ");
			free(tmp);
		}
	}
	closedir(dir);
	return (list);
}

char *replace_wildcard(char *str)
{
	char	*replaced_str;
	char	*tmp;
	char	*dir_list;
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
		if (str[i] == '*' && !in_quotes && !in_double_quotes)
		{
			dir_list = list_working_dir();
			if (dir_list == NULL)
				return (free(replaced_str), NULL);
			tmp = replaced_str;
			replaced_str = ft_strjoin(replaced_str, dir_list);
			free(tmp);
			free(dir_list);
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
		}
		i++;
		if (replaced_str == NULL)
			return (NULL);
	}
	return (replaced_str);
}

// #include <stdio.h>

// int main(int argc, char *argv[])
// {
// 	if (argc < 2)
// 		return (1);
// 	char *replaced_string;

// 	replaced_string = replace_wildcard(argv[1]);
// 	printf("%s\n", replaced_string);
// 	free(replaced_string);
// 	return (0);
// }
