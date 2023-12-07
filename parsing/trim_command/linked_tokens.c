/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 12:13:27 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/01 16:47:13 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

static t_tokens	*create_element(char *str)
{
	t_tokens	*element;

	element = ft_calloc(1, sizeof(t_tokens));
	if (!element)
		return (NULL);
	element->token = str;
	element->next = NULL;
	return (element);
}

void	append_back(char *str, t_tokens **tokens, int *error_flag)
{
	t_tokens	*current;
	t_tokens	*element;

	element = create_element(str);
	if (!element)
	{
		*error_flag = 1;
		return ;
	}
	current = *tokens;
	if (!current)
	{
		*tokens = element;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = element;
}
