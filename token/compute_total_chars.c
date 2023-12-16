/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_total_chars.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 22:46:19 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:13:57 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (empty_quotes(command, *start))
		return ((*start) += 2, 0);
	if (*state == 3 && command[*start] == '\'')
		return (-1);
	if (command[*start] != '\'')
		return (0);
	*state = 1;
	while (command[*start + i] && command[*start + i] != '\'')
		i++;
	(*start) += i + 1;
	(*total_chars) += i + 1;
	return (0);
}

int	update_total_dquote(char *command, int *start, \
int *total_chars, int *state)
{
	int	i;

	i = 1;
	if (empty_quotes(command, *start))
		return ((*start) += 2, 0);
	if (*state == 3 && command[*start] == '\"')
		return (-1);
	if (command[*start] != '\"')
		return (0);
	*state = 1;
	while (command[*start + i] != '\"')
		i++;
	(*start) += i + 1;
	(*total_chars) += i + 1;
	return (0);
}

int	compute_total_chars(char *command, int *skip)
{
	int	i;
	int	state;
	int	total_chars;

	i = 0;
	state = 0;
	total_chars = 0;
	while (in_array(command[i], TRIM_SET))
		i++;
	while (command[i] && !in_array(command[i], OPS_TRIM))
	{
		if (update_total_squote(command, &i, &total_chars, &state) == -1)
			return (*skip = i, total_chars);
		if (update_total_dquote(command, &i, &total_chars, &state) == -1)
			return (*skip = i, total_chars);
		if (update_total_cmd(command, &i, &total_chars, &state) == -1)
			return (*skip = i, total_chars);
	}
	return (*skip = i, total_chars);
}
