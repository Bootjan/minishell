/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_priorities.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 11:53:58 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/18 13:13:32 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recursive_priorities(t_tokens *next_cmd, char ***envp, int last_ret)
{
	int	ret;
	int	prior;

	ret = -1;
	if (!next_cmd)
		return (last_ret);
	prior = next_cmd->token;
	if (prior == AND_OPR && last_ret == 0)
		ret = execute_priorities(next_cmd->next, envp);
	if (prior == OR_OPR && last_ret > 0)
		ret = execute_priorities(next_cmd->next, envp);
	if (ret == -1)
		return (last_ret);
	if (prior == AND_OPR)
		return (!(ret == 0 && last_ret == 0));
	if (prior == OR_OPR)
		return (!(ret == 0 || last_ret == 0));
	return (last_ret);
}

int	execute_priorities(t_tokens *tokens, char ***envp)
{
	int			ret;
	int			len;
	t_tokens	*sub_cmd;
	t_tokens	*next_cmd;

	ret = 0;
	len = 0;
	sub_cmd = compute_sub_cmd(tokens, &len);
	next_cmd = compute_next_cmd(tokens, len);
	if (sub_cmd)
		ret = execute_sub_cmd(sub_cmd, envp);
	free_tokens(&sub_cmd, FREE_1D);
	ret = recursive_priorities(next_cmd, envp, ret);
	return (ret);
}
