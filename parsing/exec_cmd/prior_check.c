/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prior_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/29 15:32:35 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/11/29 15:32:59 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_or_prior(char *command, int i)
{
	return (command[i] == '|' && command[i + 1] == '|');
}

int	is_and_prior(char *command, int i)
{
	return (command[i] == '&' && command[i + 1] == '&');
}

int	is_priority(char *command, int i)
{
	return (is_or_prior(command, i) || is_and_prior(command, i));
}
