/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:15:09 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/07 14:04:42 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define EXPORT_TRIM " \t\r\v\n.,/\\:;<>{}[]"
# define QUOTES "\"\'"

# include "minishell.h"
# include <stdbool.h>

int		echo(int argc, char *argv[], char *envp[]);
int		pwd(int argc, char *argv[], char *envp[]);
int		export(int argc, char *argv[], char ***envp);
int		env(int argc, char *argv[], char *envp[]);
int		exit_b(int argc, char *argv[], char ***envp);
int		unset(int argc, char *argv[], char ***envp);
int		print_export(char **envp);
char	*compute_without_quotes_export(char *command);

#endif