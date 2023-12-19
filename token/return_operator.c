/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return_operator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 12:16:45 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/18 13:17:16 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_pipe(int *error_flag)
{
	char	*out;

	out = ft_strdup("|");
	if (!out)
		return (*error_flag = 1, NULL);
	return (out);
}

char	*return_and(int *error_flag)
{
	char	*out;

	out = ft_strdup("&&");
	if (!out)
		return (*error_flag = 1, NULL);
	return (out);
}

char	*return_or(int *error_flag)
{
	char	*out;

	out = ft_strdup("||");
	if (!out)
		return (*error_flag = 1, NULL);
	return (out);
}

char	*return_par_open(int *error_flag)
{
	char	*out;

	out = ft_strdup("(");
	if (!out)
		return (*error_flag = 1, NULL);
	return (out);
}

char	*return_par_close(int *error_flag)
{
	char	*out;

	out = ft_strdup(")");
	if (!out)
		return (*error_flag = 1, NULL);
	return (out);
}
