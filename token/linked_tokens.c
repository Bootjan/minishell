/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 22:48:10 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:14:05 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **tokens, int mode)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (mode == FREE_2D && current->data)
			free(current->data);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

t_tokens	*create_element(char *str, int token)
{
	t_tokens	*element;

	element = ft_calloc(1, sizeof(t_tokens));
	if (!element)
		return (NULL);
	element->data = str;
	element->token = token;
	element->next = NULL;
	return (element);
}

t_tokens	*append_back(t_tokens *tokens, char *str, int token)
{
	t_tokens	*current;
	t_tokens	*element;

	element = create_element(str, token);
	if (!element)
		return (free_tokens(&tokens, FREE_2D), NULL);
	current = tokens;
	if (!current)
		return (element);
	while (current->next)
		current = current->next;
	current->next = element;
	return (tokens);
}
