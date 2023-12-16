/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:14:17 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:27:55 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char ***envp, int j)
{
	char	*temp;

	temp = (*envp)[j];
	(*envp)[j] = (*envp)[j + 1];
	(*envp)[j + 1] = temp;
}

static char	**sort_envp(char **envp, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j]) + 1) > 0)
				swap(&envp, j);
			j++;
		}
		i++;
	}
	return (envp);
}

static int	print_sorted_envp(char ***envp, int len)
{
	int	i;

	i = 0;
	while (i < len)
		if (printf("declare -x %s\n", (*envp)[i++]) == -1)
			return (free_2d_array(envp, FREE_2D), 1);
	free_2d_array(envp, FREE_2D);
	return (0);
}

int	print_export(char **envp)
{
	int		len;
	int		ret;
	char	**temp_envp;

	len = 0;
	while (envp[len])
		len++;
	temp_envp = copy_envp(envp);
	if (!temp_envp)
		return (1);
	temp_envp = sort_envp(temp_envp, len);
	ret = print_sorted_envp(&temp_envp, len);
	return (ret);
}
