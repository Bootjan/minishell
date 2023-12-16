/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 15:36:25 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:36:58 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_before_equal(char *str)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[index] && str[index] != '=')
		index++;
	if (index == (int)ft_strlen(str) || index == 0)
		return (false);
	while (i < index)
	{
		if (in_array(str[i++], NVALID_IDEN))
			return (false);
	}
	return (true);
}

int	is_right_format(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	while (str[i])
	{
		if (in_array(str[i], EXPORT_TRIM))
			i++;
		else
			break ;
	}
	if (str[i])
		return (0);
	return (1);
}

void	replace_var(char ***envp, int i, char *new_entry)
{
	if ((*envp)[i])
		free((*envp)[i]);
	(*envp)[i] = new_entry;
}
