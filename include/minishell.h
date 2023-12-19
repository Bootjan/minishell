/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:07:47 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:31:30 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <stddef.h>
# include <string.h>
# include <linux/limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "executor.h"
# include "tokenize.h"
# include "replace.h"
# include "signal_handler.h"
# include "ansi.h"

# define PROMPT \
"\1\e[1m\e[44m\2 MINISHELL \1\e[0m\e[34m\2▓▓▒▒░░\1\e[0m\2 "
# define PROMPT_ERR \
"\1\e[1m\e[41m\2 MINISHELL \1\e[0m\e[31m\2▓▓▒▒░░\1\e[0m\2 "

# define FREE_1D 1
# define FREE_2D 2

int		minishell(char ***envp);
char	**copy_envp(char **envp);
int		arr_len(char **arr);

#endif