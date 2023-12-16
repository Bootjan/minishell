/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 14:31:13 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/15 17:28:07 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overwrite(char **var, char *with)
{
	free(*var);
	*var = with;
}

static int	update_pwd(char *pwd, char ***envp)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", pwd);
	if (tmp == NULL)
		return (1);
	*envp = add_to_envp(envp, tmp);
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
		return (1);
	tmp = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (tmp == NULL)
		return (1);
	*envp = add_to_envp(envp, tmp);
	return (0);
}

static char	*update_relative_path(char *curpath, char *pwd)
{
	if (curpath[0] != '/')
	{
		if (pwd[ft_strlen(pwd) - 1] != '/')
			overwrite(&curpath, ft_strjoin("/", curpath));
		if (curpath == NULL)
			return (NULL);
		if (curpath[ft_strlen(curpath) - 1] != '/')
			overwrite(&curpath, ft_strjoin(curpath, "/"));
		if (curpath == NULL)
			return (NULL);
		overwrite(&curpath, ft_strjoin(pwd, curpath));
		if (curpath == NULL)
			return (NULL);
	}
	return (curpath);
}

static char	*get_homepath(char ***envp)
{
	char	*home;

	home = get_envvar(*envp, "HOME");
	if (home == NULL || home[0] == '\0')
		return (NULL);
	return (ft_strdup(home));
}

int	cd(int argc, char *argv[], char ***envp)
{
	char	*pwd;
	char	*curpath;

	if (argc < 2)
		curpath = get_homepath(envp);
	else
		curpath = ft_strdup(argv[1]);
	if (curpath == NULL)
		return (1);
	pwd = get_envvar(*envp, "PWD");
	if (pwd == NULL)
		return (1);
	curpath = update_relative_path(curpath, pwd);
	if (curpath == NULL)
		return (1);
	if (chdir(curpath) == -1)
	{
		perror("cd");
		free(curpath);
		return (1);
	}
	free(curpath);
	return (update_pwd(pwd, envp));
}
