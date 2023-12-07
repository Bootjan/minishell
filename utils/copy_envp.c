/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_envp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 23:57:12 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/06 15:52:02 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char ***arr, int state)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (state == FREE_2D && (*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!envp)
		return (NULL);
	while (envp[len])
		len++;
	new_envp = ft_calloc(len + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i++])
			return (free_2d_array(&new_envp, FREE_2D), NULL);
	}
	return (new_envp);
}
