MAIN = main.c minishell.c
TOKEN = append_redir_in.c compute_token.c compute_total_chars.c linked_tokens.c find_tokens.c compute_total_chars_utils.c append_operator.c return_operator.c
REPLACE = replace_envvar.c replace_envvar_utils.c replace_wildcard.c replace_all.c remove_quotes.c remove_quotes_tokens.c replace_all_utils.c split_command_utils.c
EXECUTE = execute_builtin.c execute_first_cmd.c execute_middle_cmd.c execute_last_cmd.c execute_one_cmd.c execute_sub_cmd.c executor.c execute_priorities.c
EXECUTE_UTILS = compute_path.c execute_builtins_utils.c process_utils.c
SET_IO = do_here_doc.c set_in_output.c set_input.c set_output.c
SET_IO_PARENT = set_in_output_parent.c set_input_parent.c set_output_parent.c
UTILS = parsing_utils.c copy_envp.c print_error.c
PARSE_ERROR = parse_error.c
SIGNALS = signal_handler.c
BUILTINS = echo.c pwd.c env.c export.c export_utils.c print_export.c exit.c cd.c unset.c

SRCS = $(MAIN)\
$(TOKEN)\
$(REPLACE)\
$(EXECUTE)\
$(EXECUTE_UTILS)\
$(SET_IO)\
$(SET_IO_PARENT)\
$(UTILS)\
$(PARSE_ERROR)\
$(SIGNALS)\
$(BUILTINS)
