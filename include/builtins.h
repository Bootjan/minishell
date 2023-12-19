/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:15:09 by tsteur        #+#    #+#                 */
/*   Updated: 2023/12/19 14:27:19 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define NVALID_IDEN " \t\r\v\n.,/\\:;<>{}[]-%%*+"
# define QUOTES "\"\'"

// ### BUILTINS ################################################################
int		echo(int argc, char *argv[], char *envp[]);
int		pwd(int argc, char *argv[], char *envp[]);
int		export(int argc, char *argv[], char ***envp);
int		env(int argc, char *argv[], char *envp[]);
int		exit_b(int argc, char *argv[], char ***envp);
int		unset(int argc, char *argv[], char ***envp);
int		cd(int argc, char *argv[], char ***envp);

// ### EXPORT UTILS ############################################################
char	*compute_without_quotes_unset(char *command);
int		print_export(char **envp);
int		is_right_format(char *str);
char	**add_to_envp(char ***envp, char *new_entry);
int		check_before_equal(char *str);
void	replace_var(char ***envp, int i, char *new_entry);

#endif