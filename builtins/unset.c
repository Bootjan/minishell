/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:10:25 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/08 14:22:21 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	**func(char ***envp, int index)
{
	int		len;
	int		i;
	int		j;
	char	**new_envp;

	len = 0;
	i = 0;
	j = 0;
	while ((*envp)[len])
		len++;
	new_envp = ft_calloc(len, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (i < len)
	{
		if (i == index && (*envp)[i])
			free((*envp)[i++]);
		else
			new_envp[j++] = (*envp)[i++];
	}
	free_2d_array(envp, FREE_1D);
	return (new_envp);
}

char	**func2(char ***envp, char *clean_av)
{
	int	i;
	int	av_len;

	i = 0;
	av_len = ft_strlen(clean_av);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], clean_av, av_len) == 0 && \
		(*envp)[i][av_len] == '=')
			return (func(envp, i));
		i++;
	}
	return (*envp);
}

int	unset_var(char *argv, char ***envp)
{
	char	*clean_av;

	if (unclosed_quotes(argv))
		return (1);
	clean_av = compute_without_quotes_export(argv);
	if (!clean_av)
		return (1);
	if (is_right_format(clean_av))
		*envp = func2(envp, clean_av);
	free(clean_av);
	if (!*envp)
		return (1);
	return (0);
}

int	unset(int argc, char *argv[], char ***envp)
{
	int	i;
	int	ret;
	
	i = 1;
	ret = 0;
	if (argc == 1)
		return (0);
	while (i < argc && ret == 0)
		ret = unset_var(argv[i++], envp);
	return (ret);
}
