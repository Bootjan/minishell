/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:14:17 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 18:48:23 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	swap_elements(char ***envp, int j)
{
	char	*temp;

	temp = (*envp)[j];
	(*envp)[j] = (*envp)[j + 1];
	(*envp)[j + 1] = temp;
}

static char	**sort_envp(char **envp, int len)
{
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j]) + 1) > 0)
				swap_elements(&envp, j);
			j++;
		}
		i++;
	}
	return (envp);
}

int	print_export(char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	envp = sort_envp(envp, len);
	while (i < len)
		if (printf("declare -x %s\n", envp[i++]) == -1)
			return (1);
	return (0);
}
