/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_envvar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 13:08:07 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/18 12:09:01 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_ret_val(char *replaced_str, int last_ret, int *i)
{
	char	*replacement;
	char	*out;

	replacement = ft_itoa(last_ret);
	if (replacement == NULL)
		return (free(replaced_str), NULL);
	out = ft_strjoin(replaced_str, replacement);
	free(replaced_str);
	free(replacement);
	(*i)++;
	return (out);
}

static char	*replace_vars(char **envp, char *replaced_str, \
char *curr_el, int *i)
{
	char	*tmp;
	char	*replacement;
	char	chrstr[2];

	chrstr[1] = '\0';
	tmp = strdup_to_endofvar(curr_el);
	if (tmp == NULL)
		return (free(replaced_str), NULL);
	if (tmp[0] == '\0')
	{
		chrstr[0] = '$';
		replacement = chrstr;
	}
	else
		replacement = get_envvar(envp, tmp);
	free(tmp);
	if (replacement)
	{
		tmp = replaced_str;
		replaced_str = ft_strjoin(replaced_str, replacement);
		free(tmp);
	}
	(*i) += strlen_to_endofvar(curr_el);
	return (replaced_str);
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

char	*replace_envvar(char *str, int last_ret, char **envp)
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
		if (str[i] == '$' && in_quotes != IN_SQUOTES)
		{
			i++;
			if (str[i] == '?')
				replaced_str = replace_ret_val(replaced_str, last_ret, &i);
			else
				replaced_str = replace_vars(envp, replaced_str, &(str[i]), &i);
		}
		else
			replaced_str = replace_char(replaced_str, &in_quotes, str[i++]);
		if (replaced_str == NULL)
			return (NULL);
	}
	return (replaced_str);
}
