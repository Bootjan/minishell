/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 15:30:46 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/01 16:38:54 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	list_len(t_cmds *cmds)
{
	int		len;
	t_cmds	*current;

	len = 0;
	current = cmds;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	free_list(t_cmds **cmds)
{
	t_cmds	*current;
	t_cmds	*next;

	next = NULL;
	current = *cmds;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*cmds = NULL;
}

static t_cmds	*create_element(char *cmd)
{
	t_cmds	*element;

	element = ft_calloc(1, sizeof(t_cmds));
	if (!element)
		return (NULL);
	element->data = cmd;
	element->next = NULL;
	return (element);
}

void	push_back(t_cmds **cmds, char *cmd)
{
	t_cmds	*element;
	t_cmds	*current;

	element = create_element(cmd);
	if (!element)
		perror_exit("Malloc error:", STD_EXIT);
	current = *cmds;
	if (!current)
	{
		*cmds = element;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = element;
}
