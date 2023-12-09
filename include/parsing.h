/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:26:10 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/09 17:28:12 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "builtins.h"

# define OPERATORS "<>|&"
# define TRIM_SET " \t\v"
# define OPS_TRIM "<>|& \t\v"
# define OPS_TRIM_QUOTES "<>|& \t\v\"\'"
# define STD_EXIT 127

# define ECHO_INT 1
# define EXPORT_INT 2
# define ENV_INT 3
# define PWD_INT 4
# define CD_INT 5
# define UNSET_INT 6
# define EXIT_INT 7
# define ECHO_STR "echo"
# define EXPORT_STR "export"
# define ENV_STR "env"
# define PWD_STR "pwd"
# define CD_STR "cd"
# define UNSET_STR "unset"
# define EXIT_STR "exit"

typedef struct s_tokens {
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_pipes {
	int		fd_out_prev;
	int		fd_in_prev;
	int		fd_out_curr;
	int		fd_in_curr;
}	t_pipes;

typedef struct s_cmds {
	char			*data;
	struct s_cmds	*next;
}	t_cmds;

int		add_chars(char **out, char *command, int total_chars);
int		compute_total_chars_cmd(char *command);
char	*compute_first_cmd(char *command);
int		skip_redir(char *command, char redir);
int		exec_builtin_parent(char *command, char ***envp, int builtin);
int		is_builtin(char *cmd);
void	exec_builtin_child(char ***cmds, char ***envp, int builtin);

// ### PROCESS UTILS ###########################################################
void	init_pipe(t_pipes *pipes);
void	close_pipes(t_pipes pipes);
int		do_fork(void);
void	do_dup2(int fd, int new_fd);
void	wait_for_childs(int num);
void	perror_exit(char *msg, int exit_code);
int		check_status(int status);
void	update_command(char **command, int pid);
int		part_of_subcmd(char c);
int		check_status(int status);

// ### PRIOR CHECKER ###########################################################
int		is_or_prior(char *command, int i);
int		is_and_prior(char *command, int i);
int		is_priority(char *command, int i);

// ### COMPUTE PATH ############################################################
char	*compute_path(char **envp, char *cmd);

// ### CMDS ####################################################################
int		do_commands(char *command, char ***envp);
int		do_one_cmd(char *command, char ***envp);
void	do_first_cmd(char **command, char **envp, t_pipes *pipes, int *pid);
void	do_middle_cmd(char **command, char **envp, t_pipes *pipes, int *pid);
void	do_last_cmd(char *command, char **envp, t_pipes pipes, int *pid);

// ### LINKED LIST PARSING #####################################################
void	push_back(t_cmds **cmds, char *cmd);
void	free_list(t_cmds **cmds);
int		list_len(t_cmds *cmds);

// ### PARSE COMMAND ###########################################################
char	**parse_command(char *command, int *fd_in, int *fd_out);
int		set_input(char *command, int *fd_in, char **here_doc);
int		set_output(char *command, int *fd_out);
char	*compute_without_quotes(char *command, int *end);

// ### TRIM UTILS ##############################################################
int		in_array(char c, char *set);
int		is_command(char c);

// ### LINKED TOKENS ###########################################################
void	free_tokens(t_tokens **tokens);
void	append_back(char *str, t_tokens **tokens, int *error_flag);

// ### TRIM COMMAND ############################################################
char	*trim_command(char *command);
int		append_command(char *command, int start, \
t_tokens **tokens, int *error_flag);
char	*concat_tokens(t_tokens *tokens);

// ### UPDATE TOTAL CHARS ######################################################
int		update_total_ops(char *command, int *start, \
int *total_chars, int *state);
int		update_total_cmd(char *command, int *start, \
int *total_chars, int *state);
int		update_total_squote(char *command, int *start, \
int *total_chars, int *state);
int		update_total_dquote(char *command, int *start, \
int *total_chars, int *state);

// ### PARSE ERROR #############################################################
int		parse_error(char *command);
int		unclosed_quotes(char *command);

#endif