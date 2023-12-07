/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 13:23:08 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/06 16:13:58 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "minishell.h"

int	is_right_format(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (0);
	while (str[i] && !in_array(str[i], EXPORT_TRIM))
		i++;
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

int	replace_in_envp(char ***envp, char *new_entry)
{
	int		end;
	int		i;

	end = 0;
	while (new_entry[end] && new_entry[end] != '=')
		end++;
	if (end == (int)ft_strlen(new_entry))
		return (free(new_entry), 1);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], new_entry, end + 1) == 0)
			return (replace_var(envp, i, new_entry), 1);
		i++;
	}
	return (0);
}

char	**add_to_envp(char ***envp, char *new_entry)
{
	int		len;
	int		i;
	char	**new_envp;

	len = 0;
	i = 0;
	new_envp = NULL;
	if (replace_in_envp(envp, new_entry) == 1)
		return (*envp);
	while ((*envp)[len])
		len++;
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
		return (free_2d_array(envp, FREE_2D), NULL);
	while (i < len)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	free_2d_array(envp, FREE_1D);
	new_envp[i] = new_entry;
	return (new_envp);
}

int	export(int argc, char *argv[], char ***envp)
{
	int		i;
	char	*clean_av;

	i = 1;
	if (argc == 1)
		return (print_export(*envp));
	while (i < argc)
	{
		if (unclosed_quotes(argv[i]))
		{
			i++;
			continue ;
		}
		clean_av = compute_without_quotes_export(argv[i]);
		if (!clean_av)
			return (1);
		if (is_right_format(clean_av))
			*envp = add_to_envp(envp, clean_av);
		if (!*envp)
			return (free(clean_av), 1);
		i++;
	}
	return (0);
}
