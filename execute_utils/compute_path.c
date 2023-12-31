/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_path.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 12:03:57 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/19 16:40:35 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*compute_poss_path(char *path, char *sub_cmd)
{
	int		i;
	int		j;
	char	*out;

	out = ft_calloc(ft_strlen(path) + ft_strlen(sub_cmd) + 2, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (path[i])
		out[j++] = path[i++];
	out[j++] = '/';
	i = 0;
	while (sub_cmd[i])
		out[j++] = sub_cmd[i++];
	return (out);
}

static char	*compute_right_path(char **paths, char *cmd)
{
	char	*poss_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		poss_path = compute_poss_path(paths[i++], cmd);
		if (!poss_path)
			return (NULL);
		if (access(poss_path, X_OK) == 0)
			return (poss_path);
		free(poss_path);
	}
	return (NULL);
}

static char	**compute_paths(char **envp)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	if (path)
		paths = ft_split(&path[5], ":");
	if (!paths)
		return (NULL);
	return (paths);
}

char	*compute_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = compute_paths(envp);
	if (!paths)
		return (NULL);
	path = compute_right_path(paths, cmd);
	free_2d_array(&paths, FREE_2D);
	if (!path)
		return (NULL);
	return (path);
}
