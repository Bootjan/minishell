/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   concat_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 11:52:40 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/11/30 13:39:17 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	tokens_len(t_tokens *tokens)
{
	int			len;
	t_tokens	*current;

	len = 0;
	current = tokens;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

static int	compute_total_chars(t_tokens *tokens)
{
	int			len;
	t_tokens	*current;

	len = 0;
	current = tokens;
	while (current)
	{
		len += ft_strlen(current->token);
		current = current->next;
	}
	return (len);
}

static int	concat_current(char **command, char *str, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (start != 0)
		(*command)[start + j++] = ' ';
	while (str[i])
		(*command)[start + j++] = str[i++];
	return (j);
}

char	*concat_tokens(t_tokens *tokens)
{
	int			i;
	int			total_chars;
	char		*command;
	t_tokens	*current;

	i = 0;
	total_chars = compute_total_chars(tokens);
	total_chars += tokens_len(tokens) - 1;
	command = ft_calloc(total_chars + 1, sizeof(char));
	if (!command)
		return (NULL);
	current = tokens;
	while (current)
	{
		i += concat_current(&command, current->token, i);
		current = current->next;
	}
	return (command);
}
