/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:14:17 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/06 16:44:31 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	**sort_envp(char **envp, int len)
{
	int		i;
	int		j;
	char	*temp;

	i = len- 1;
	while (i-- >= 0)
	{
		j = len - 1;
		while (j > 0)
		{
			if (ft_strncmp(envp[j], envp[j - 1], ft_strlen(envp[j]) + 1) < 0)
			{
				temp = envp[j];
				envp[j] = envp[j - 1];
				envp[j - 1] = temp;
			}
			j--;
		}
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
