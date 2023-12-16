/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 15:19:04 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/16 15:46:52 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_H
# define REPLACE_H

# define EXPORT_TRIM "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMOPQRSTUVWXYZ0123456789_= "

# define IN_SQUOTES 1
# define IN_DQUOTES 2
# define WORKING_DIR "."

// ### REPLACE WILDCARD AND ENVVAR #############################################
char		*replace_envvar(char *str, int last_ret, char **envp);
char		*replace_wildcard(char *str);

// ### REPLACE UTILS ###########################################################
char		*replace_char(char *replaced_str, int *in_quotes, char curr_el);
int			strlen_to_endofvar(char *s);
char		*strdup_to_endofvar(char *s);
char		*get_envvar(char **envp, char *ptr);
t_tokens	*replace_wildcard_envvar(t_tokens *tokens, \
int last_ret, char **envp);

// ### REFORMAT TOKENS #########################################################
char		*remove_quotes(char *command);
char		*replace_str(char *str, int last_ret, char **envp);
t_tokens	*reformat_token(t_tokens *token, char **split_str, int *error_flag);

// ### HANDLING QUOTES #########################################################
int			is_quote(char c);
int			is_open_quote(char *command);
t_tokens	*remove_quotes_tokens(t_tokens *tokens);
int			skip_quote(char *command, char quote);

// ### SPLIT COMMAND UTILS #####################################################
int			compute_total_words(char *command);
char		**do_split(char *command, char **out);

#endif