NAME	:= so_long
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -g -no-pie
MLX_FLAGS := -Lmlx-linux -lmlx -L/usr/X11/lib -lXext -lX11 -lbsd

# Library Paths - No Spaces Around '='
LIBFT_DIR	:= libft
PRINTF_DIR	:= $(LIBFT_DIR)/ft_printf
GNL_DIR		:= $(LIBFT_DIR)/get_next_line
MLX_DIR		:= mlx-linux

# Source Files
SRCS := so_long.c \
		so_long_utils.c \

OBJS := $(SRCS:.c=.o)

# Explicit Library Paths
LIBFT_A		:= $(LIBFT_DIR)/libft.a
PRINTF_A	:= $(PRINTF_DIR)/libftprintf.a
GNL_A		:= $(GNL_DIR)/get_next_line
MLX_A		:= $(MLX_DIR)/libmlx.a

# Main Target
all: libft ft_printf mlx gnl $(NAME)

# Executable Creation
$(NAME): $(OBJS) $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o
	@echo "Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIBFT_A) $(PRINTF_A) $(MLX_FLAGS)

# Library Compilation
libft:
	$(MAKE) -C $(LIBFT_DIR)

ft_printf: libft
	$(MAKE) -C $(PRINTF_DIR)

gnl:
	$(CC) $(FLAGS) -c $(GNL_DIR)/get_next_line.c -o $(GNL_DIR)/get_next_line.o
	$(CC) $(FLAGS) -c $(GNL_DIR)/get_next_line_utils.c -o $(GNL_DIR)/get_next_line_utils.o

mlx:
	$(MAKE) -C $(MLX_DIR)

# Compilation Rule
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Cleaning Rules
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft ft_printf mlx