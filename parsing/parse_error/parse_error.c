/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:11:53 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/09 22:30:41 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	unclosed_quotes(char *command)
{
	int		i;
	char	found_quote;

	i = 0;
	found_quote = '\0';
	while (command && command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
			found_quote = command[i++];
		while (command[i] && found_quote && command[i] != found_quote)
			i++;
		if (command[i])
		{
			found_quote = '\0';
			i++;
		}
		else
			return (1);
	}
	return (0);
}

// static int	amount_of_priorities(char *command)
// {
// 	int	i;
// 	int	total;

// 	i = 0;
// 	total = 0;
// 	while (command[i] && command[i + 1])
// 	{
// 		if (is_priority(command, i++))
// 		{
// 			i++;
// 			total++;
// 		}
// 	}
// 	return (total);
// }

// static int	skip_to_prior(char *command, int i)
// {
// 	int	end;

// 	end = i;
// 	while (command[end] && command[end + 1] && !is_priority(command, end))
// 		end++;
// 	return (end - i + 2);
// }

// static int	check_between_priorities(char *command)
// {
// 	int	i;
// 	int	total;

// 	i = 0;
// 	if (!command)
// 		return (1);
// 	total = amount_of_priorities(command);
// 	if (total == 0)
// 		return (1);
// 	while (total-- > 0)
// 	{
// 		while (in_array(command[i], TRIM_SET))
// 			i++;
// 		if (command[i] && command[i + 1] && is_and_prior(command, i))
// 			return (0);
// 		i += skip_to_prior(command, i);
// 	}
// 	while (in_array(command[i], TRIM_SET))
// 		i++;
// 	if (command[i])
// 		return (1);
// 	return (0);
// }

int	parse_error(char *command)
{
	if (unclosed_quotes(command))
		return (1);
	// if (!check_between_priorities(command))
	// 	return (1);
	return (0);
}
