NAME	:= so_long
CC		:= cc
FLAGS	:= -Wall -Wextra -Werror -g
MLX_FLAGS := -Lminilibx-linux -lmlx -L/usr/X11/lib -lXext -lX11 -lbsd

# Library Paths - No Spaces Around '='
LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux

# Source Files
SRCS := so_long.c \
		so_long_utils.c \
		so_long_fts.c \
		so_long_keys.c \
		so_long_map.c \
		so_long_map_utils.c

OBJS := $(SRCS:.c=.o)

# Explicit Library Paths
LIBFT_A		:= $(LIBFT_DIR)/libft.a
MLX_A		:= $(MLX_DIR)/libmlx_Linux.a

# Main Target
all: $(NAME)

# Executable Creation
$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@echo "Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIBFT_A) $(MLX_FLAGS)

# Library Compilation
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

# Compilation Rule
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Cleaning Rules
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re