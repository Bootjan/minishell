/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 23:11:53 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 16:22:28 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unclosed_parenthesis(char *command)
{
	int		i;
	bool	open;

	i = 0;
	open = false;
	while (command[i])
	{
		if (command[i] == '(' && open == true)
			return (1);
		if (command[i] == '(')
			open = true;
		if (command[i] == ')' && open == false)
			return (1);
		if (command[i] == ')')
			open = false;
		i++;
	}
	return (open);
}

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
		return (UNCL_QUOTES);
	if (unclosed_parenthesis(command))
		return (UNCL_PAR);
	return (0);
}
