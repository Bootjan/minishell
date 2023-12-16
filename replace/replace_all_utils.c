/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_all_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 16:51:33 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/16 15:54:02 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_str(char *str, int last_ret, char **envp)
{
	char	*envvar_str;
	char	*wildcard_str;

	envvar_str = replace_envvar(str, last_ret, envp);
	if (!envvar_str)
		return (NULL);
	wildcard_str = replace_wildcard(envvar_str);
	ft_free_str(&envvar_str);
	if (!wildcard_str)
		return (NULL);
	return (wildcard_str);
}

static t_tokens	*append_new_tokens(t_tokens *current, \
char **split_str, int token, int *error_flag)
{
	int			i;
	int			len;
	t_tokens	*element;

	i = 1;
	len = arr_len(split_str);
	while (i < len)
	{
		element = create_element(split_str[i++], token);
		if (!element)
			return (*error_flag = 1, \
			free_2d_array(&split_str, FREE_2D), current);
		current->next = element;
		current = current->next;
	}
	free(split_str);
	return (current);
}

t_tokens	*reformat_token(t_tokens *token, char **split_str, int *error_flag)
{
	t_tokens	*current;
	t_tokens	*next;

	current = token;
	next = current->next;
	free(current->data);
	current->data = split_str[0];
	current = append_new_tokens(current, split_str, token->token, error_flag);
	if (*error_flag != 0)
		return (token);
	current->next = next;
	return (token);
}
