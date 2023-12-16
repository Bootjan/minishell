/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 22:47:15 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/15 17:24:00 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef struct s_tokens
{
	char			*data;
	int				token;
	struct s_tokens	*next;
}	t_tokens;

# define OPERATORS "<>|&"
# define TRIM_SET " \t\v"
# define OPS_TRIM "<>|& \t\v"
# define HERE_DOC 1
# define REDIR_IN 2
# define REDIR_APP 3
# define REDIR_TRUNC 4
# define CMD 5
# define PIPE 6
# define AND_OPR 7
# define OR_OPR 8

// ### LINKED TOKENS ###########################################################
t_tokens	*find_tokens(char *command);
void		free_tokens(t_tokens **tokens, int mode);
t_tokens	*append_back(t_tokens *tokens, char *str, int token);
t_tokens	*create_element(char *str, int token);

// ### COMPUTE TOTAL CHARS #####################################################
int			compute_total_chars(char *command, int *skip);
int			only_empty_quotes(char *command);
char		*compute_token(char *command, int *skip);
int			empty_quotes(char *command, int start);

// ### UTILS ###################################################################
int			is_command(char c);
int			in_array(char c, char *set);

// ### APPEND TOKEN ############################################################
int			append_redir_out(char *command, t_tokens **tokens, int *error_flag);
int			append_redir_in(char *command, t_tokens **tokens, int *error_flag);
int			append_operator(char *command, t_tokens **tokens, int *error_flag);
int			append_command(char *command, t_tokens **tokens, int *error_flag);

#endif