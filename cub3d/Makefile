NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADERS = include/cub3d.h
# Paths
MLX42_DIR = MLX42
LIBFT_DIR = libft

# Libraries
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = src/main.c \
      src/init.c \
      src/hooks.c \
      src/parse_map.c \
      src/validate_map.c \
      src/render.c \
      src/load_textures.c \
      src/debug.c \
      get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

# Includes
INCLUDES = -Iinclude -I$(MLX42_DIR)/include -I$(LIBFT_DIR) -Iget_next_line

# MLX42 and GLFW flags
MLX_FLAGS = $(MLX42_LIB) -ldl -lglfw -pthread -lm -lGL

# Compiler and linker flags
LDFLAGS =

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42_LIB)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(MLX_FLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX42_LIB):
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build -j4

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re
