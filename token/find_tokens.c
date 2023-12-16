/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_tokens.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 22:52:39 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:02 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(char c)
{
	return (!in_array(c, OPS_TRIM) && c != '\"' && c != '\'');
}

t_tokens	*find_tokens(char *command)
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
		else if (command[i] == '<')
			i += append_redir_in(&(command[i + 1]), &tokens, &error_flag);
		else if (command[i] == '>')
			i += append_redir_out(&(command[i + 1]), &tokens, &error_flag);
		else if (in_array(command[i], OPERATORS))
			i += append_operator(&(command[i]), &tokens, &error_flag);
		else
			i += append_command(&(command[i]), &tokens, &error_flag);
	}
	if (error_flag != 0)
		return (free_tokens(&tokens, FREE_2D), NULL);
	return (tokens);
}
