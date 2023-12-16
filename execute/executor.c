/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 01:19:28 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:19:10 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*compute_next_cmd(t_tokens *tokens)
{
	t_tokens	*out;

	out = tokens;
	while (out && out->token != OR_OPR && out->token != AND_OPR)
		out = out->next;
	return (out);
}

int	len_sub_cmd(t_tokens *tokens)
{
	int			len;
	t_tokens	*current;

	len = 0;
	current = tokens;
	if (!current)
		return (0);
	while (current)
	{
		if (current->token == OR_OPR || current->token == AND_OPR)
			return (len);
		len++;
		current = current->next;
	}
	return (len);
}

t_tokens	*compute_sub_cmd(t_tokens *tokens)
{
	int			len;
	t_tokens	*out;
	t_tokens	*current;

	len = len_sub_cmd(tokens);
	out = NULL;
	current = tokens;
	if (len == 0)
		return (NULL);
	while (len-- > 0)
	{
		out = append_back(out, current->data, current->token);
		if (!out)
			return (free_tokens(&out, FREE_1D), NULL);
		current = current->next;
	}
	return (out);
}

int	executor(t_tokens *tokens, char ***envp)
{
	int			ret;
	t_tokens	*sub_cmd;
	t_tokens	*next_cmd;

	ret = 0;
	next_cmd = compute_next_cmd(tokens);
	sub_cmd = compute_sub_cmd(tokens);
	if (sub_cmd)
		ret = execute_sub_cmd(sub_cmd, envp);
	free_tokens(&sub_cmd, FREE_1D);
	if (ret == 0 && next_cmd && next_cmd->token == AND_OPR)
		ret = executor(next_cmd->next, envp);
	else if (ret > 0 && next_cmd && next_cmd->token == OR_OPR)
		ret = executor(next_cmd->next, envp);
	return (ret);
}
