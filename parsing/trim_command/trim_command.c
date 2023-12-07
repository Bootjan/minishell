/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 12:19:08 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/04 20:15:44 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	in_array(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

int	is_command(char c)
{
	return (!in_array(c, OPS_TRIM) && c != '\"' && c != '\'');
}

static t_tokens	*find_tokens(char *command)
{
	int			i;
	int			error_flag;
	t_tokens	*tokens;

	i = 0;
	error_flag = 0;
	tokens = NULL;
	while (command[i] && error_flag == 0)
	{
		if (in_array(command[i], TRIM_SET))
			i++;
		else
			i += append_command(command, i, &tokens, &error_flag);
	}
	if (error_flag != 0)
		return (free_tokens(&tokens), NULL);
	return (tokens);
}

char	*trim_command(char *command)
{
	char		*clean_command;
	t_tokens	*tokens;

	tokens = NULL;
	tokens = find_tokens(command);
	if (!tokens)
		return (NULL);
	clean_command = concat_tokens(tokens);
	free_tokens(&tokens);
	if (!clean_command)
		return (NULL);
	return (clean_command);
}
