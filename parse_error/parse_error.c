/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 23:11:53 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:19:41 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(char *command)
{
	int		i;
	char	found_quote;

	i = 0;
	found_quote = '\0';
	while (command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
			found_quote = command[i++];
		while (command[i] && found_quote && command[i] != found_quote)
			i++;
		if (command[i])
		{
			found_quote = '\0';
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	parse_error(char *command)
{
	if (!command)
		return (0);
	if (unclosed_quotes(command))
		return (1);
	return (0);
}
