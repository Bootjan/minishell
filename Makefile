MAIN = main.c minishell.c
EXEC = exec_cmd.c get_path.c prior_check.c process_utils.c \
one_cmd.c first_cmd.c middle_cmd.c last_cmd.c one_cmd_utils.c exec_builtin.c
SET_IO = linked_list.c parse_command.c set_input.c set_output.c compute_without_quotes.c
TRIM = append_command.c concat_tokens.c linked_tokens.c trim_command.c update_total_chars.c
PARSE_ERROR = parse_error.c
REPLACE = replace_envvar.c replace_wildcard.c
UTILS = parsing_utils.c copy_envp.c
SIGNALS = signal_handler.c
BUILTINS = echo.c pwd.c env.c export.c export_utils.c print_export.c exit.c unset.c

SRCS = $(MAIN)\
$(EXEC)\
$(SET_IO)\
$(TRIM)\
$(PARSE_ERROR)\
$(REPLACE)\
$(UTILS)\
$(SIGNALS)\
$(BUILTINS)\
print_error.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
NAME = minishell
VPATH = . parsing/exec_cmd parsing/set_in_out_put parsing/trim_command parsing/parse_error \
replace utils signals builtins builtins/export

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g#,leak -g
LDFLAGS = -lreadline
OBJS_DIR = ./objs

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libft
INCLUDE_LIB = -L./libft -lft

RM = rm -f

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(INCLUDE_LIB)
	@echo "./$(NAME) made!"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "./objs made!"

$(OBJS): $(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:	
	@make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJS_DIR)
	@echo "$(NAME) objects removed!"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "./$(NAME) removed!"
	@rm -rf $(OBJS_DIR)
	@echo "./objs removed!"

re: fclean all

.PHONY: all clean re fclean
