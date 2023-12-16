/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_total_chars_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 16:58:11 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:13:53 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_quotes(char *command, int start)
{
	char	quote;

	quote = command[start];
	if (quote != '\'' && quote != '\"')
		return (0);
	if (command[start + 1] == quote)
		return (1);
	return (0);
}

int	only_empty_quotes(char *command)
{
	if (!empty_quotes(command, 0))
		return (0);
	if (!command[2] || in_array(command[2], OPS_TRIM))
		return (1);
	return (0);
}
