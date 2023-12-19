/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 01:19:28 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/18 12:39:49 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*compute_next_cmd(t_tokens *tokens, int len)
{
	t_tokens	*out;

	out = tokens;
	while (out && len-- > 0)
		out = out->next;
	return (out);
}

static int	prior_len(t_tokens *tokens)
{
	int			len;
	t_tokens	*current;

	len = 0;
	current = tokens;
	if (!current)
		return (0);
	while (current && current->token != PAR_CLOSE)
	{
		len++;
		current = current->next;
	}
	return (len + 2);
}

int	len_sub_cmd(t_tokens *tokens)
{
	int			len;
	t_tokens	*current;

	len = 0;
	current = tokens;
	if (!current)
		return (0);
	if (current->token == PAR_OPEN || current->token == PAR_CLOSE)
		return (prior_len(tokens->next));
	while (current)
	{
		if (current->token >= AND_OPR && current->token <= PAR_CLOSE)
			return (len);
		len++;
		current = current->next;
	}
	return (len);
}

t_tokens	*compute_sub_cmd(t_tokens *tokens, int *len)
{
	int			len_cmd;
	t_tokens	*out;
	t_tokens	*current;

	len_cmd = len_sub_cmd(tokens);
	*len = len_cmd;
	out = NULL;
	current = tokens;
	if (len_cmd == 0)
		return (NULL);
	while (len_cmd-- > 0)
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
	int			len;
	t_tokens	*sub_cmd;
	t_tokens	*next_cmd;

	ret = 0;
	len = 0;
	sub_cmd = compute_sub_cmd(tokens, &len);
	next_cmd = compute_next_cmd(tokens, len);
	if (sub_cmd && sub_cmd->token == PAR_OPEN)
		ret = execute_priorities(sub_cmd->next, envp);
	else if (sub_cmd)
		ret = execute_sub_cmd(sub_cmd, envp);
	free_tokens(&sub_cmd, FREE_1D);
	if (ret == 0 && next_cmd && next_cmd->token == AND_OPR)
		ret = executor(next_cmd->next, envp);
	else if (ret > 0 && next_cmd && next_cmd->token == OR_OPR)
		ret = executor(next_cmd->next, envp);
	return (ret);
}
