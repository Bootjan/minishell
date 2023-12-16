/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_tokens.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 14:42:16 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/16 15:20:23 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	skip_quote(char *command, char quote)
{
	int	i;

	i = 0;
	while (command[i] && command[i] != quote)
		i++;
	if (!command[i])
		return (i);
	return (i + 1);
}

int	is_open_quote(char *command)
{
	int		i;
	char	quote;

	i = 1;
	quote = command[0];
	while (command[i] && command[i] != quote)
	{
		if (is_quote(command[i]) && !is_open_quote(&(command[i])))
			i += skip_quote(&(command[i + 1]), command[i]);
		else
			i++;
	}
	if (!command[i])
		return (1);
	return (0);
}

t_tokens	*remove_quotes_tokens(t_tokens *tokens)
{
	char		*clean_str;
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		clean_str = remove_quotes(current->data);
		current->data = clean_str;
		if (!clean_str)
			return (free_tokens(&tokens, FREE_2D), NULL);
		current = current->next;
	}
	return (tokens);
}
