FT_PRINTF = ft_helper.c ft_printf.c ft_print_u_d_i.c \
ft_print_p_x_ux.c ft_print_per_s_c.c ft_base_converter.c
GNL = get_next_line.c get_next_line_utils.c

SRCS = $(FT_PRINTF)\
$(GNL)
VPATH = . ./get_next_line ./ft_printf

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

ARRCS = ar rcs
NAME = libft.a

REMOVE = rm -f

CC = cc
CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MAIN = main.c

all: $(NAME)

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS)
	@cp	$(LIBFT) $(NAME)
	@$(ARRCS) $(NAME) $(OBJS)
	@echo "Libft.a made!"

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "./objs made!"

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "Libft objects removed!"

fclean:	clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "Libft.a removed!"

re: fclean all

.PHONY: all clean fclean re
