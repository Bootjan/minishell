/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:46:51 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/16 22:10:05 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_command(char *command, t_tokens **tokens, int *error_flag)
{
	int		skip;
	char	*data;

	skip = 0;
	data = compute_token(command, &skip);
	if (!data)
		return (*error_flag = 1, 0);
	*tokens = append_back(*tokens, data, CMD);
	if (!*tokens)
		return (free(data), *error_flag = 1, 0);
	return (skip);
}

int	append_redir_out(char *command, t_tokens **tokens, int *error_flag)
{
	int		skip;
	int		token;
	char	*data;

	skip = 0;
	if (command[0] == '>')
	{
		data = compute_token(&(command[1]), &skip);
		skip += 2;
		token = REDIR_APP;
	}
	else
	{
		data = compute_token(command, &skip);
		skip++;
		token = REDIR_TRUNC;
	}
	if (!data)
		return (*error_flag = 1, 0);
	*tokens = append_back(*tokens, data, token);
	if (!*tokens)
		return (free(data), *error_flag = 1, 0);
	return (skip);
}

int	append_redir_in(char *command, t_tokens **tokens, int *error_flag)
{
	int		skip;
	int		token;
	char	*data;

	skip = 0;
	if (command[0] == '<')
	{
		data = compute_token(&(command[1]), &skip);
		skip += 2;
		token = HERE_DOC;
	}
	else
	{
		data = compute_token(command, &skip);
		skip++;
		token = REDIR_IN;
	}
	if (!data)
		return (*error_flag = 1, 0);
	*tokens = append_back(*tokens, data, token);
	if (!*tokens)
		return (free(data), *error_flag = 1, 0);
	return (skip);
}
