/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:07:47 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 22:30:30 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "parsing.h"
# include "ansi.h"

// # define PROMPT BOLD BLUE_FG "MINISHELL" RESET BLUE_FG " ❱ " RESET

# define PROMPT "\1" BOLD BLUE_BG "\2" " MINISHELL " "\1" RESET BLUE_FG "\2" "▓▓" "\1" "▒▒░░" "\1" RESET "\2" " "
# define PROMPT_ERR "\1" BOLD RED_BG "\2" " MINISHELL " "\1" RESET RED_FG "\2" "▓▓" "\1" "▒▒░░" "\1" RESET "\2" " "
# define FREE_1D 1
# define FREE_2D 2
 	
int		minishell(char **envp);
void	free_2d_array(char ***arr, int state);
char	**copy_envp(char **envp);
void	print_error_cmd(char *cmd);
void	print_error_open(char *file);

#endif