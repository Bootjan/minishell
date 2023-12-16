/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_wildcard.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 11:24:57 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:12:39 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_ent(DIR *dir, struct dirent *ent, char **list)
{
	char	*tmp;

	tmp = NULL;
	while (ent != NULL && *list != NULL)
	{
		if (ent->d_name[0] != '.')
		{
			tmp = *list;
			*list = ft_strjoin(*list, ent->d_name);
			free(tmp);
		}
		ent = readdir(dir);
		if (ent != NULL && ent->d_name[0] != '.' && *list != NULL
			&& (*list)[0] != '\0')
		{
			tmp = *list;
			*list = ft_strjoin(*list, " ");
			free(tmp);
		}
	}
}

static char	*list_working_dir(void)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*list;

	dir = opendir(WORKING_DIR);
	if (dir == NULL)
		return (NULL);
	list = ft_strdup("");
	ent = readdir(dir);
	update_ent(dir, ent, &list);
	closedir(dir);
	return (list);
}

static char	*replace_ast(char *replaced_str)
{
	char	*out;
	char	*dir_list;

	dir_list = list_working_dir();
	if (dir_list == NULL)
		return (free(replaced_str), NULL);
	out = ft_strjoin(replaced_str, dir_list);
	free(replaced_str);
	free(dir_list);
	return (out);
}

char	*replace_char(char *replaced_str, int *in_quotes, char curr_el)
{
	char	*out;
	char	chrstr[2];

	chrstr[1] = '\0';
	if (curr_el == '\"' && *in_quotes == IN_DQUOTES)
		*in_quotes = false;
	else if (curr_el == '\"' && *in_quotes == false)
		*in_quotes = IN_DQUOTES;
	else if (curr_el == '\'' && *in_quotes == IN_SQUOTES)
		*in_quotes = false;
	else if (curr_el == '\'' && *in_quotes == false)
		*in_quotes = IN_SQUOTES;
	chrstr[0] = curr_el;
	out = ft_strjoin(replaced_str, chrstr);
	free(replaced_str);
	return (out);
}

char	*replace_wildcard(char *str)
{
	int		i;
	int		in_quotes;
	char	*replaced_str;

	in_quotes = false;
	replaced_str = ft_strdup("");
	if (replaced_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '*' && !in_quotes)
			replaced_str = replace_ast(replaced_str);
		else
			replaced_str = replace_char(replaced_str, &in_quotes, str[i]);
		i++;
		if (replaced_str == NULL)
			return (NULL);
	}
	return (replaced_str);
}
