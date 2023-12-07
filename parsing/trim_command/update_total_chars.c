/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_total_chars.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 20:08:53 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/04 20:45:27 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	update_total_ops(char *command, int *start, \
int *total_chars, int *state)
{
	if (*state == 2 && in_array(command[*start], OPERATORS))
		return (-1);
	while (in_array(command[*start], OPERATORS))
	{
		*state = 2;
		(*start)++;
		(*total_chars)++;
	}
	return (0);
}

int	update_total_cmd(char *command, int *start, \
int *total_chars, int *state)
{
	if (*state == 3 && command[*start] && is_command(command[*start]))
		return (-1);
	while (command[*start] && is_command(command[*start]))
	{
		*state = 1;
		(*start)++;
		(*total_chars)++;
	}
	return (0);
}

int	update_total_squote(char *command, int *start, \
int *total_chars, int *state)
{
	int	i;

	i = 1;
	if (*state == 3 && command[*start] == '\'')
		return (-1);
	if (command[*start] != '\'')
		return (0);
	*state = 1;
	while (command[*start + i] != '\'')
		i++;
	(*start) += i + 1;
	if (i > 1)
		(*total_chars) += i + 1;
	return (0);
}

int	update_total_dquote(char *command, int *start, \
int *total_chars, int *state)
{
	int	i;

	i = 1;
	if (*state == 3 && command[*start] == '\"')
		return (-1);
	if (command[*start] != '\"')
		return (0);
	*state = 1;
	while (command[*start + i] != '\"')
		i++;
	(*start) += i + 1;
	if (i > 1)
		(*total_chars) += i + 1;
	return (0);
}
