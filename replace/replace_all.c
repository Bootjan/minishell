/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_all.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:51:15 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/18 10:29:01 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

static char	**split_command(char *command)
{
	int		total_words;
	char	**out;

	total_words = compute_total_words(command);
	out = ft_calloc(total_words + 1, sizeof(char *));
	if (!out)
		return (NULL);
	out = do_split(command, out);
	if (!out)
		return (NULL);
	return (out);
}

t_tokens	*replace(t_tokens *current, int last_ret, \
char **envp, int *error_flag)
{
	char	*replaced_str;
	char	**split_str;

	replaced_str = replace_str(current->data, last_ret, envp);
	if (!replaced_str)
		return (*error_flag = 1, current);
	if (ft_strncmp(replaced_str, current->data, ft_strlen(current->data)) == 0)
		return (ft_free_str(&replaced_str), current);
	split_str = split_command(replaced_str);
	ft_free_str(&replaced_str);
	if (!split_str)
		return (*error_flag = 1, current);
	return (reformat_token(current, split_str, error_flag));
}

t_tokens	*replace_wildcard_envvar(t_tokens *tokens, \
int last_ret, char **envp)
{
	int			error_flag;
	t_tokens	*current;
	t_tokens	*next;

	error_flag = 0;
	current = tokens;
	while (current && error_flag == 0)
	{
		next = current->next;
		current = replace(current, last_ret, envp, &error_flag);
		current = next;
	}
	if (error_flag != 0)
		return (free_tokens(&tokens, FREE_2D), NULL);
	return (tokens);
}
