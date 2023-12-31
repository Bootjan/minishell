/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append_operator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 22:04:16 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 12:24:05 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*compute_data(char *command, int *token, int *skip, int *error_flag)
{
	char	*data;

	data = NULL;
	if (command[0] == '|' && command[1] != '|')
		return (*skip = 1, *token = PIPE, return_pipe(error_flag));
	else if (command[0] == '&' && command[1] == '&')
		return (*token = AND_OPR, return_and(error_flag));
	else if (command[0] == '|' | command[1] == '|')
		return (*token = OR_OPR, return_or(error_flag));
	else if (command[0] == '(')
		return (*skip = 1, *token = PAR_OPEN, return_par_open(error_flag));
	else if (command[0] == ')')
		return (*skip = 1, *token = PAR_CLOSE, return_par_close(error_flag));
	else
		*skip = 1;
	return (data);
}

int	append_operator(char *command, t_tokens **tokens, int *error_flag)
{
	int		skip;
	int		token;
	char	*data;

	skip = 2;
	data = compute_data(command, &token, &skip, error_flag);
	if (*error_flag != 0)
		return (0);
	if (data)
		*tokens = append_back(*tokens, data, token);
	return (skip);
	if (!*tokens)
		return (free(data), *error_flag = 1, 0);
	return (skip);
}
