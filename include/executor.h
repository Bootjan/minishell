/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:32:28 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/15 17:27:22 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tokenize.h"
# include "builtins.h"

typedef struct s_pipes
{
	int		fd_out_prev;
	int		fd_in_prev;
	int		fd_out_curr;
	int		fd_in_curr;
}	t_pipes;

typedef struct s_builtin_fds
{
	int	fd_in;
	int	fd_out;
	int	new_in;
	int	new_out;
}	t_builtin_fds;

# define STD_EXIT 127
# define FREE_1D 1
# define FREE_2D 2

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

// ### UTILS ###################################################################
int				parse_error(char *command);
int				unclosed_quotes(char *command);
t_tokens		*update_command(t_tokens *tokens);
int				check_status(int status);
void			free_2d_array(char ***arr, int mode);

// ### PRINT ERRORS ############################################################
void			print_error_cmd(char *cmd);
void			print_error_open(char *file);
void			perror_exit(char *msg, int exit_code);

// ### EXECUTE BUILTIN #########################################################
int				is_builtin(char *cmd);
void			execute_builtin_child(char	**cmds, \
char **envp, int builtin_int);
int				execute_builtin_parent(t_tokens *tokens, \
char ***envp, int builtin);

// ### SET IN/OUTPUT PARENT ####################################################
int				set_input_parent(t_tokens *current, \
int *fd_in, char **here_doc);
int				set_output_parent(t_tokens *current, int *fd_out);
char			**set_in_output_parent(t_tokens *cmd, \
t_builtin_fds *fds, char **here_doc);

// ### SET IN/OUTPUT CHILD #####################################################
char			**set_in_output(t_tokens *cmd, int *fd_in, int *fd_out);
char			*do_here_doc(char *limiter);
void			set_input(t_tokens *current, int *fd_in, char **here_doc);
void			set_output(t_tokens *current, int *fd_out);
void			write_here_doc_to_pipe(char *here_doc, int *fd_in);

// ### PROCESS UTILS ###########################################################
int				do_fork(void);
void			init_pipe(t_pipes *pipes);
void			close_pipes(t_pipes pipes);
void			do_dup2(int fd, int new_fd);
void			wait_for_childs(int num);
char			*compute_path(char **envp, char *cmd);

// ### EXECUTORS ###############################################################
int				executor(t_tokens *tokens, char ***envp);
int				execute_sub_cmd(t_tokens *cmd, char ***envp);
int				execute_one_cmd(t_tokens *cmd, char ***envp);
t_tokens		*execute_first_cmd(t_tokens *cmd, char **envp, \
t_pipes *pipes, int *pid);
t_tokens		*execute_middle_cmd(t_tokens *cmd, char **envp, \
t_pipes *pipes, int *pid);
int				execute_last_cmd(t_tokens *cmd, char **envp, t_pipes pipes);
int				execute_builtin(char **cmds, char ***envp, int builtin);

#endif