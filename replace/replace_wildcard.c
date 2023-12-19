/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_wildcard.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 11:24:57 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/18 13:48:20 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_ent(DIR *dir, char **list, char *prefix, char *suffix)
{
	char			*tmp;
	struct dirent	*ent;

	ent = readdir(dir);
	while (ent != NULL && *list != NULL)
	{
		if ((ent->d_name[0] != '.' || prefix[0] == '.') \
			&& *list != NULL && \
			ft_strncmp(prefix, ent->d_name, ft_strlen(prefix)) == 0 && \
			ft_strlen(ent->d_name) >= ft_strlen(suffix) && \
			ft_strncmp(suffix, ent->d_name + ft_strlen(ent->d_name) \
					- ft_strlen(suffix), ft_strlen(suffix) + 1) == 0)
		{
			if (ft_strlen(*list) != 0)
			{
				tmp = *list;
				*list = ft_strjoin(*list, " ");
				free(tmp);
			}
			tmp = *list;
			*list = ft_strjoin(*list, ent->d_name);
			free(tmp);
		}
		ent = readdir(dir);
	}
}

static char	*list_working_dir(char *prefix, char *suffix)
{
	DIR				*dir;
	char			*list;

	dir = opendir(WORKING_DIR);
	if (dir == NULL)
		return (NULL);
	list = ft_strdup("");
	update_ent(dir, &list, prefix, suffix);
	closedir(dir);
	return (list);
}

char	*find_asterisk(char *str)
{
	int		i;
	int		in_quotes;
	char	*asterisk;

	in_quotes = false;
	asterisk = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_quotes == IN_DQUOTES)
			in_quotes = false;
		else if (str[i] == '\"' && in_quotes == false)
			in_quotes = IN_DQUOTES;
		else if (str[i] == '\'' && in_quotes == IN_SQUOTES)
			in_quotes = false;
		else if (str[i] == '\'' && in_quotes == false)
			in_quotes = IN_SQUOTES;
		if (str[i] == '*' && !in_quotes && asterisk == NULL)
			asterisk = str + i;
		else if (str[i] == '*' && !in_quotes && asterisk != NULL)
			return (NULL);
		i++;
	}
	return (asterisk);
}

void	get_fixes(char *str, char *asterisk, char **prefix, char **suffix)
{
	char	*tmp;

	*prefix = str;
	*asterisk = '\0';
	*suffix = asterisk + 1;
	tmp = ft_strdup(*prefix);
	if (tmp == NULL)
		*prefix = NULL;
	else
		*prefix = remove_quotes(tmp);
	tmp = ft_strdup(*suffix);
	if (tmp == NULL)
		suffix = NULL;
	else
		*suffix = remove_quotes(tmp);
}

char	*replace_wildcard(char *str)
{
	char	*prefix;
	char	*suffix;
	char	*asterisk;
	char	*list;

	asterisk = find_asterisk(str);
	if (asterisk == NULL)
		return (strdup(str));
	get_fixes(str, asterisk, &prefix, &suffix);
	if (prefix == NULL && suffix == NULL)
		return (NULL);
	if (prefix == NULL)
		return (free(suffix), NULL);
	if (suffix == NULL)
		return (free(prefix), NULL);
	list = list_working_dir(prefix, suffix);
	free(prefix);
	free(suffix);
	return (list);
}
