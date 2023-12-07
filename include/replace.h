/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 15:19:04 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/07 11:42:31 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_H
# define REPLACE_H

char	*replace_envvar(char *str, int last_ret, char **envp);
char	*replace_wildcard(char *str);

#endif