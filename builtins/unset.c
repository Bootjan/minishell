/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 11:10:25 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:18 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**remove_from_envp(char ***envp, int index)
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

static int	found_match(char *curr_envp, char *clean_av, int av_len)
{
	return (ft_strncmp(curr_envp, clean_av, av_len) == 0
		&& curr_envp[av_len] == '=');
}

static char	**find_and_remove(char ***envp, char *argv)
{
	int	i;
	int	av_len;

	i = 0;
	av_len = ft_strlen(argv);
	while ((*envp)[i])
	{
		if (found_match((*envp)[i], argv, av_len))
			return (remove_from_envp(envp, i));
		i++;
	}
	return (*envp);
}

int	unset_var(char *argv, char ***envp)
{
	if (is_right_format(argv))
		*envp = find_and_remove(envp, argv);
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
