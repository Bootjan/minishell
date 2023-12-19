include makerc/srcs.mk

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
NAME = minishell
VPATH = . execute execute_utils set_in_output token replace utils signals builtins builtins/export parse_error set_in_output_parent

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
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
