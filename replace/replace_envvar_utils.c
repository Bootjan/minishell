/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_envvar_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:49:45 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:12:32 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_to_endofvar(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && ft_strchr(EXPORT_TRIM, s[len]))
		len++;
	return (len);
}

char	*strdup_to_endofvar(char *s)
{
	int		size;
	char	*out;

	size = strlen_to_endofvar(s) + 1;
	out = ft_calloc(size, sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s, size - 1);
	return (out);
}

char	*get_envvar(char **envp, char *ptr)
{
	char	**current_var;

	current_var = envp;
	while (*current_var != NULL)
	{
		if (ft_strncmp(*current_var, ptr, ft_strlen(ptr)) == 0
			&& (*current_var)[ft_strlen(ptr)] == '=')
			return (&(*current_var)[ft_strlen(ptr) + 1]);
		current_var++;
	}
	return (NULL);
}
